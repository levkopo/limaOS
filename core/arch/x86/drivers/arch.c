#include <arch.h>
#include "include/IDT.h"

void arch_init() {
    idt_init();
}