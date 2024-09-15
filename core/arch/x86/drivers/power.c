//
// Created by levkopo on 9/5/24.
//
#include <screen.h>
#include <panic.h>
#include <power.h>

uint8_t* power_manager = (uint8_t*) POWER_MANAGER_ADDRESS;

extern void apm_real_mode();

void power_control_init() {

}

void shutdown() {
    uint16_t current_power_manager = *power_manager;
    switch (current_power_manager) {
        case POWER_APM:
            println_string("Send apm power off...");
            apm_real_mode();
            break;

        case POWER_NONE:
            panic("Power manager not initialized");
    }
}