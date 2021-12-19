#include "include/kernel.h"

void fs_init() {

}

void init() {
    init_vga();
    idt_init();
    mem_init();
}

extern "C" void kmain() {
    init();

    println_string("    __ _                   ___  __     ");
    println_string("   / /(_)_ __ ___   __ _  /___\\/ _\\  ");
    println_string("  / / | | '_ ` _ \\ / _` |//  //\\ \\  ");
    println_string(" / /__| | | | | | | (_| / \\_// _\\ \\ ");
    println_string(" \\____/_|_| |_| |_|\\__,_\\___/  \\__/");
    println();
    println_string(" Version 0.1 - Alpha. Based on DmNSOS");
    while (1) {
        print_string("> ");
        char *line = readline();

        if (strcmp(line, "exit") == 0) {
            return;
        } else if (strcmp(line, "hello") == 0) {
            println_string("Hello!");
        } else {
            print_string(line);
            println_string(": not found");
        }
    }
}