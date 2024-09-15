#ifndef __AHCI_H_
#define __AHCI_H_

#include <stdbool.h>
#include <stdlib.h>
#include "ahci_structs.h"
#include "ata_structs.h"

typedef struct _HBA {
    HBA_MEM *mem;

    uint32_t bus;
    uint32_t slot;
    uint32_t function;

    uint16_t vendorid;
    uint16_t deviceid;

    OS_DRIVE drives[32];
    void (*refresh_hba)();

    uint8_t is_active;
} OS_HBA;

typedef struct _DRIVE_UI {
    uint8_t port_num;
    uint32_t port;
    uint8_t active;
} DRIVE_UI;

typedef struct _AHCI_DEV_UI {
    uint32_t ABAR;

    uint32_t bus;
    uint32_t slot;
    uint32_t function;

    uint16_t vendorid;
    uint16_t deviceid;

    DRIVE_UI drives[32];
} AHCI_DEV_UI;

#define HBA_PxCMD_CR 	0x8000
#define HBA_PxCMD_FR 	0x4000
#define HBA_PxCMD_FRE	0x0010
#define HBA_PxCMD_ST 	0x0001

#define	SATA_SIG_ATA	0x00000101	// SATA drive
#define	SATA_SIG_ATAPI	0xEB140101	// SATAPI drive
#define	SATA_SIG_SEMB	0xC33C0101	// Enclosure management bridge
#define	SATA_SIG_PM		0x96690101	// Port multiplier

#define ATA_DEV_BUSY 0x80
#define ATA_DEV_DRQ 0x08

#define WRITE_TO_DEV 	1
#define READ_FROM_DEV 	0

int probe_ahci2(AHCI_DEV_UI *ahci_dev);
void refresh_hba(OS_HBA *self);

int ata_command(HBA_PORT *port, uint8_t *regs, uint8_t *buf, uint32_t buf_len, uint8_t direction);
int ata_command_no_wait(HBA_PORT *port, uint8_t *regs, uint8_t *buf, uint32_t buf_len, uint8_t direction);

int wait_for_not_busy(HBA_PORT *port, int timeout);
int wait_for_completion(HBA_PORT *port, int slot, int timeout);
int find_cmdslot(HBA_PORT *port);

int reset_port(HBA_PORT *port);

#endif