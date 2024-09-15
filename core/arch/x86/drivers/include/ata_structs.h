#ifndef ATA_STRUCTS_H
#define ATA_STRUCTS_H

#include <stdint.h>

typedef struct _IDENTIFY_DEVICE_DATA {
    uint8_t		general_config[2];
    uint8_t		serial[21];
    uint8_t		firmware[9];
    uint8_t		model[41];
    uint8_t		world_wide[9];

    uint8_t		sec_level:1;
    uint8_t		sec_enh_erase_sup:1;
    uint8_t		sec_count_exp:1;
    uint8_t		sec_frozen:1;
    uint8_t		sec_locked:1;
    uint8_t		sec_enabled:1;
    uint8_t		sec_supported:1;

    uint16_t	sec_erase_time;
    uint16_t	sec_enh_erase_time;

    uint8_t		cmd_feat_supported_83[2];

    uint64_t	max_lba;
} IDENTIFY_DEVICE_DATA;

typedef struct _SMART_DATA {
    uint8_t self_test_status;
    uint8_t smart_capability[2];
    uint16_t self_test_short_poll;
    uint16_t self_test_ext_poll;
} SMART_DATA;

typedef struct _OS_DRIVE {
    HBA_PORT *port;
    uint32_t port_num;

    IDENTIFY_DEVICE_DATA id;
    void (*refresh_identify)();

    uint8_t is_active;
} OS_DRIVE;

#endif //ATA_STRUCTS_H