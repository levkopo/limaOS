#include <stdlib.h>
#include "include/ahci.h"
#include "include/ata.h"

int identify_device(HBA_PORT *port, IDENTIFY_DEVICE_DATA *id) {
    memset(id, 0, sizeof(IDENTIFY_DEVICE_DATA));

    uint8_t regs[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xec, 0x00};
    uint8_t buf[512];
    if (ata_command(port, regs, buf, 512, READ_FROM_DEV)) {
        memcpy(id->general_config, buf, 2);
        memcpy(id->serial, buf+20, 20);
        memcpy(id->firmware, buf+46, 8);
        memcpy(id->model, buf+54, 40);
        memcpy(id->world_wide, buf+216, 8);

        id->sec_supported = buf[256]&1;
        id->sec_enabled = (buf[256]>>1)&1;
        id->sec_locked = (buf[256]>>2)&1;
        id->sec_frozen = (buf[256]>>3)&1;
        id->sec_count_exp = (buf[256]>>4)&1;
        id->sec_enh_erase_sup = (buf[256]>>5)&1;
        id->sec_level = buf[257]&1;

        id->sec_erase_time = (uint16_t)(buf[179]<<8) | buf[178];
        id->sec_enh_erase_time = (uint16_t)(buf[181]<<8) | buf[180];

        id->max_lba = 0;
        int i, o=0;
        for (i=200; i<208; i++) {
            id->max_lba |= ((uint64_t)buf[i]) << (o*8);
            o++;
        }

        byte_swap(id->serial, 20);
        byte_swap(id->model, 40);
        byte_swap(id->firmware, 8);

        return 1;
    }
    return 0;
}

void refresh_identify(OS_DRIVE *self) {
    identify_device(self->port, &self->id);
}

int smart_read_data(HBA_PORT *port, SMART_DATA *sd) {
    uint8_t regs[8] = {0xd0, 0x00, 0x00, 0x4f, 0xc2, 0x00, 0xb0, 0x00};
    uint8_t buf[512];
    if (ata_command(port, regs, buf, 512, READ_FROM_DEV)) {
        memcpy(&sd->self_test_status, buf+363, 1);
        memcpy(sd->smart_capability, buf+368, 2);

        sd->self_test_short_poll = (uint16_t)buf[372];
        sd->self_test_ext_poll = (buf[373]==0xff)?(((uint16_t)buf[376]<<8)|buf[375]):buf[373];
        return 1;
    }
    return 0;
}

int smart_execute_offline_immediate(HBA_PORT *port, uint8_t subcommand) {
    uint8_t regs[8] = {0xd4, 0x00, subcommand, 0x4f, 0xc2, 0x00, 0xb0, 0x00};
    uint8_t buf[512];
    return ata_command(port, regs, buf, 512, WRITE_TO_DEV);
}

int smart_read_log(HBA_PORT *port, uint8_t log_page, uint8_t *buf, unsigned int count) {
    uint8_t regs[8] = {0xd5, (uint8_t)(count/512), log_page, 0x4f, 0xc2, 0x00, 0xb0, 0x00};
    return ata_command(port, regs, buf, count, READ_FROM_DEV);
}

int smart_write_log(HBA_PORT *port, uint8_t log_page, uint8_t *buf, unsigned int count) {
    uint8_t regs[8] = {0xd6, (uint8_t)(count/512), log_page, 0x4f, 0xc2, 0x00, 0xb0, 0x00};
    return ata_command(port, regs, buf, count, WRITE_TO_DEV);
}

int smart_enable_operations(HBA_PORT *port) {
    uint8_t regs[8] = {0xd8, 0x00, 0x00, 0x4f, 0xc2, 0x00, 0xb0, 0x00};
    uint8_t buf[512];
    return ata_command(port, regs, buf, 512, WRITE_TO_DEV);
}

int smart_disable_operations(HBA_PORT *port) {
    uint8_t regs[8] = {0xd9, 0x00, 0x00, 0x4f, 0xc2, 0x00, 0xb0, 0x00};
    uint8_t buf[512];
    return ata_command(port, regs, buf, 512, WRITE_TO_DEV);
}

int smart_return_status(HBA_PORT *port, uint8_t log_page) {
    uint8_t regs[8] = {0xda, 0x00, log_page, 0x4f, 0xc2, 0x00, 0xb0, 0x00};
    uint8_t buf[512];
    return ata_command(port, regs, buf, 512, WRITE_TO_DEV);
}



int security_set_password(HBA_PORT *port, uint8_t set_master, uint8_t sec_level, uint8_t *password) {
    uint8_t regs[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf1, 0x00};
    uint8_t buf[512] = {set_master, sec_level};
    memcpy(buf+2, password, 32);
    return ata_command(port, regs, buf, 512, WRITE_TO_DEV);
}

int security_unlock(HBA_PORT *port, uint8_t compare_master, uint8_t *password) {
    uint8_t regs[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf2, 0x00};
    uint8_t buf[512] = {compare_master};
    memcpy(buf+2, password, 32);
    return ata_command(port, regs, buf, 512, WRITE_TO_DEV);
}

int security_erase_prepare(HBA_PORT *port) {
    uint8_t regs[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf3, 0x00};
    uint8_t buf[512];
    return ata_command(port, regs, buf, 512, WRITE_TO_DEV);
}

int security_erase_unit(HBA_PORT *port, uint8_t compare_master, uint8_t enhanced_erase, uint8_t *password) {
    uint8_t regs[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf4, 0x00};
    uint8_t buf[512] = {compare_master, enhanced_erase};
    memcpy(buf+2, password, 32);
    return ata_command_no_wait(port, regs, buf, 512, WRITE_TO_DEV);
}

int security_freeze_lock(HBA_PORT *port) {
    uint8_t regs[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf5, 0x00};
    uint8_t buf[512];
    return ata_command(port, regs, buf, 512, WRITE_TO_DEV);
}

int security_disable_password(HBA_PORT *port, uint8_t compare_master, uint8_t *password) {
    uint8_t regs[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf6, 0x00};
    uint8_t buf[512] = {compare_master};
    memcpy(buf+2, password, 32);
    return ata_command(port, regs, buf, 512, WRITE_TO_DEV);
}