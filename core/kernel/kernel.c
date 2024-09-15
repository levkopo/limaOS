#include <kernel.h>
#include <arch.h>
#include <power.h>
#include <panic.h>

void start_main_process() {
    char buffer [sizeof(int)*8+1];

    println_string("    __ _                   ___  __     ");
    println_string("   / /(_)_ __ ___   __ _  /___\\/ _\\  ");
    println_string("  / / | | '_ ` _ \\ / _` |//  //\\ \\  ");
    println_string(" / /__| | | | | | | (_| / \\_// _\\ \\ ");
    println_string(" \\____/_|_| |_| |_|\\__,_\\___/  \\__/");
    println();
    print_string("BIOS area hardware: ");
    print_string(itoa(detect_bios_area_hardware(), buffer, 10));
    print_string(":");
    println_string(itoa(detect_bios_area_hardware(), buffer, 2));

    print_string("Display type: ");
    switch (video_type) {
        case VIDEO_TYPE_COLOUR:
            println_string("colour");
            break;
        case VIDEO_TYPE_MONOCHROME:
            println_string("monochrome");
            break;
        case VIDEO_TYPE_NONE:
            println_string("none");
            break;
    }

    while (1) {
        print_string("> ");
        char *line = readline();

        if (strcmp(line, "exit") == 0) {
            shutdown();
            return;
        } else if (strcmp(line, "hello") == 0) {
            println_string("Hello!");
        } else {
            print_string(line);
            println_string(": not found");
        }
    }
}

void kmain() {
    arch_init();
    mem_init();
    vga_init();
    power_control_init();

    play_sound(425000);

    start_main_process();
    panic("Main process excited");
}

void kernel_panic() {
    while (1) {

    }
}