//
// Created by levkopo on 9/5/24.
//
#include <panic.h>
#include <screen.h>

void panic(char *str) {
    clear_vga_buffer(&vga_buffer);
    println_string("KERNEL PANIC");
    println_string("Save a logs, send to developer and shutdown device.");
    print_string("Message: ");
    println_string(str);
    asm("jmp kernel_panic");
}