#include <stdlib.h>
#include <io.h>
#include "include/ata.h"
#include "include/ahci.h"

int ata_command(HBA_PORT *port, uint8_t *regs, uint8_t *buf, uint32_t buf_len, uint8_t direction) {
    port->is = (uint32_t)-1;

    int slot = find_cmdslot(port);

    HBA_CMD_HEADER *cmdheader = (HBA_CMD_HEADER*)port->clb;
    cmdheader += slot;
    cmdheader->cfl = sizeof(FIS_REG_H2D)/sizeof(uint32_t);
    cmdheader->w = direction;
    cmdheader->prdtl = (uint16_t)(((buf_len-1)>>9)>>4) + 1;

    HBA_CMD_TBL *cmdtbl = (HBA_CMD_TBL*)(cmdheader->ctba);
    memset(cmdtbl, 0, sizeof(HBA_CMD_TBL) + (cmdheader->prdtl-1)*sizeof(HBA_PRDT_ENTRY));

    int i, dbc;
    for (i=0; i<cmdheader->prdtl; i++) {
        dbc = (8192>buf_len)? buf_len:8192;
        cmdtbl->prdt_entry[i].dba = (uint32_t)buf;
        cmdtbl->prdt_entry[i].dbc = dbc-1; // "Bit ‘0’ of this field must always be ‘1’ to indicate an even byte count." (AHCI Spec 1.3.1 Pg.43)
        cmdtbl->prdt_entry[i].i = 1;
        buf += dbc;
        buf_len -= dbc;
    }

    FIS_REG_H2D *cmdfis = (FIS_REG_H2D*)(&cmdtbl->cfis);
    cmdfis->fis_type = FIS_TYPE_REG_H2D;
    cmdfis->c = 1;

    cmdfis->featurel 	= regs[0];
    cmdfis->countl 		= regs[1];
    cmdfis->lba0 		= regs[2];
    cmdfis->lba1 		= regs[3];
    cmdfis->lba2 		= regs[4];
    cmdfis->device 		= regs[5];
    cmdfis->command 	= regs[6];


    if (wait_for_not_busy(port, 2000)) {
        port->ci = 1<<slot; // issue command

        if (wait_for_completion(port, slot, 2000)) {
            // check task file data for a fail

            return 1;
        }
    }
    return 0;
}

int ata_command_no_wait(HBA_PORT *port, uint8_t *regs, uint8_t *buf, uint32_t buf_len, uint8_t direction) {
    port->is = (uint32_t)-1;

    int slot = find_cmdslot(port);

    HBA_CMD_HEADER *cmdheader = (HBA_CMD_HEADER*)port->clb;
    cmdheader += slot;
    cmdheader->cfl = sizeof(FIS_REG_H2D)/sizeof(uint32_t);
    cmdheader->w = direction;
    cmdheader->prdtl = (uint16_t)(((buf_len-1)>>9)>>4) + 1;

    HBA_CMD_TBL *cmdtbl = (HBA_CMD_TBL*)(cmdheader->ctba);
    memset(cmdtbl, 0, sizeof(HBA_CMD_TBL) + (cmdheader->prdtl-1)*sizeof(HBA_PRDT_ENTRY));

    int i, dbc;
    for (i=0; i<cmdheader->prdtl; i++) {
        dbc = (8192>buf_len)? buf_len:8192;
        cmdtbl->prdt_entry[i].dba = (uint32_t)buf;
        cmdtbl->prdt_entry[i].dbc = dbc-1; // "Bit ‘0’ of this field must always be ‘1’ to indicate an even byte count." (AHCI Spec 1.3.1 Pg.43)
        cmdtbl->prdt_entry[i].i = 1;
        buf += dbc;
        buf_len -= dbc;
    }

    FIS_REG_H2D *cmdfis = (FIS_REG_H2D*)(&cmdtbl->cfis);
    cmdfis->fis_type = FIS_TYPE_REG_H2D;
    cmdfis->c = 1;

    cmdfis->featurel 	= regs[0];
    cmdfis->countl 		= regs[1];
    cmdfis->lba0 		= regs[2];
    cmdfis->lba1 		= regs[3];
    cmdfis->lba2 		= regs[4];
    cmdfis->device 		= regs[5];
    cmdfis->command 	= regs[6];


    if (wait_for_not_busy(port, 2000)) {
        port->ci = 1<<slot; // issue command
        return 1;
    }

    return 0;
}

int wait_for_not_busy(HBA_PORT *port, int timeout) {
    while (timeout>0) {
        if ((port->tfd & (ATA_DEV_BUSY | ATA_DEV_DRQ)) == 0) break;
        msleep(1);
        timeout--;
    }
    if (timeout==0)
        return 0;
    else
        return 1;
}

int wait_for_completion(HBA_PORT *port, int slot, int timeout) {
    while (timeout>0) {
        if ((port->ci & (1<<slot)) == 0) break;
        msleep(1);
        timeout--;
    }
    if (timeout==0)
        return 0;
    else
        return 1;
}

int find_cmdslot(HBA_PORT *port) {
    uint32_t slots = (port->sact | port->ci);
    for (int i=0; i<32; i++)
    {
        if ((slots&1) == 0)
            return i;
        slots >>= 1;
    }
    return -1;
}

int reset_port(HBA_PORT *port) {
    // clear CMD.ST
    port->cmd &= 0xFFFFFFFE;

    // wait for CMD.CR to clear
    int timeout = 500;
    while (timeout>0) {
        if ((port->cmd & HBA_PxCMD_CR) == 0) break;
        msleep(1);
        timeout--;
    }

    // write 1 to SCTL.DET
    port->sctl = ((port->sctl & 0xFFFFFFF0) | 1);

    // wait a least a millisecond to ensure a comreset happened
    msleep(1);

    // clear SCTL.DET to 0
    port->sctl &= 0xFFFFFFF0;

    // wait for coms to be re-established
    timeout = 2000;
    while (timeout>0) {
        if (port->ssts & 1) break;
        msleep(1);
        timeout--;
    }

    // clear any error bits resulting from reset
    port->serr = 0xFFFFFFFF;

    if (timeout==0)
        return 0;
    else
        return 1;
}


int probe_ahci2(AHCI_DEV_UI *ahci_dev) {
    HBA_MEM *ahci_mem = (HBA_MEM*)ahci_dev->ABAR;

    int port, current_drive=0;
    for (port=0;port<32;port++) {
        if (ahci_mem->pi & (1<<port)) {
            uint8_t ssts_ipm = (ahci_mem->ports[port].ssts >> 8) & 0x0F;
            uint8_t	ssts_det = ahci_mem->ports[port].ssts & 0x0F;

            if (ssts_ipm && ssts_det) {
                // make sure port started
                if (!(ahci_mem->ports[port].cmd & HBA_PxCMD_ST)) {
                    ahci_mem->ports[port].cmd |= (HBA_PxCMD_ST|HBA_PxCMD_FRE);
                }
                // clear status
                ahci_mem->ports[port].serr = ahci_mem->ports[port].serr;
                ahci_mem->ports[port].is = ahci_mem->ports[port].is;
                ahci_mem->ports[port].cmd |= HBA_PxCMD_ST;

                ahci_dev->drives[current_drive].port_num = port;
                ahci_dev->drives[current_drive].port = (uint32_t)&ahci_mem->ports[port];
                ahci_dev->drives[current_drive].active = 1;
                current_drive++;
            }
        }
    }

    return current_drive;
}

void refresh_hba(OS_HBA *self) {
    int port;
    for (port=0;port<32;port++) {
        if (self->mem->pi & (1<<port)) {
            uint8_t ssts_ipm = (self->mem->ports[port].ssts >> 8) & 0x0F;
            uint8_t	ssts_det = (self->mem->ports[port].ssts >> 0) & 0x0F;

            if (ssts_ipm && ssts_det) {
                self->mem->ports[port].cmd |= HBA_PxCMD_ST;

                self->drives[port].port_num = port;
                self->drives[port].port = &self->mem->ports[port];
                self->drives[port].refresh_identify = refresh_identify;
                self->drives[port].is_active = true;
            }
        }
    }
}