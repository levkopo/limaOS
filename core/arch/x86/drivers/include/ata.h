#ifndef ATA_H
#define ATA_H

#include "ahci_structs.h"
#include "ata_structs.h"

int identify_device(HBA_PORT *port, IDENTIFY_DEVICE_DATA *id);
void refresh_identify(OS_DRIVE *self);

int smart_read_data(HBA_PORT *port, SMART_DATA *sd);
int smart_execute_offline_immediate(HBA_PORT *port, uint8_t subcommand);
int smart_read_log(HBA_PORT *port, uint8_t log_page, uint8_t *buf, unsigned int count);
int smart_write_log(HBA_PORT *port, uint8_t log_page, uint8_t *buf, unsigned int count);
int smart_enable_operations(HBA_PORT *port);
int smart_disable_operations(HBA_PORT *port);
int smart_return_status(HBA_PORT *port, uint8_t log_page);

int security_set_password(HBA_PORT *port, uint8_t set_master, uint8_t sec_level, uint8_t *password);
int security_unlock(HBA_PORT *port, uint8_t compare_master, uint8_t *password);
int security_erase_prepare(HBA_PORT *port);
int security_erase_unit(HBA_PORT *port, uint8_t compare_master, uint8_t enhanced_erase, uint8_t *password);
int security_freeze_lock(HBA_PORT *port);
int security_disable_password(HBA_PORT *port, uint8_t compare_master, uint8_t *password);

#endif //ATA_H