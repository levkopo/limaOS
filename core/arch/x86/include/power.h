//
// Created by levkopo on 9/5/24.
//

#ifndef LIMAOS_APM_H
#define LIMAOS_APM_H

#define POWER_MANAGER_ADDRESS 0x7000
#define POWER_NONE 0x0
#define POWER_APM 0x1

void power_control_init();
void shutdown();

#endif //LIMAOS_APM_H
