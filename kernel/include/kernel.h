#ifndef KERNEL_H
#define KERNEL_H

extern "C" {
    #include "setjmp.h"
    #include "screen.h"
    #include "alloc.h"
    #include "ahci.h"
    #include "IDT.h"
    #include "io.h"
}

#endif //KERNEL_H