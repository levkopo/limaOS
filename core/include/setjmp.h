#ifndef SETJMP_H
#define SETJMP_H

#include "stdint.h"

typedef struct {
    uint32_t ebx;
    uint32_t esi;
    uint32_t edi;
    uint32_t ebp;
    uint32_t esp;
    uint32_t eip;
} jmp_buf;

__attribute__((noinline, noclone, returns_twice, optimize(0)))
int setjmp(jmp_buf*);

__attribute__((noinline, noclone, optimize(0)))
void longjmp(jmp_buf*, int);

#endif //SETJMP_H