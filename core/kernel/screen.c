#include <screen.h>
#define COLOUR_DISPLAY_ADDRESS 0xB8000
#define MONOCHROME_DISPLAY_ADDRESS 0xB0000

enum VIDEO_TYPE video_type;
uint16_t* vga_buffer;
uint8_t vga_w = 80;
uint8_t vga_h = 25;
uint32_t vga_index, next_line_index = 1;

void vga_init(void) {
    video_type = get_bios_area_video_type();
    switch (video_type) {
        case VIDEO_TYPE_COLOUR:
            vga_buffer = (uint16_t*) COLOUR_DISPLAY_ADDRESS;
            break;
        case VIDEO_TYPE_MONOCHROME:
            vga_buffer = (uint16_t*) MONOCHROME_DISPLAY_ADDRESS;
            break;
        case VIDEO_TYPE_NONE:
            //TODO: com port
            return;
    }

    vga_enable_cursor(0, 0);
    clear_vga_buffer(&vga_buffer);
}

uint16_t detect_bios_area_hardware(void) {
    const uint16_t* bda_detected_hardware_ptr = (const uint16_t*) 0x410;
    return *bda_detected_hardware_ptr;
}

enum VIDEO_TYPE get_bios_area_video_type(void) {
    return (enum VIDEO_TYPE) (detect_bios_area_hardware() & 0x30);
}

uint16_t vga_entry(unsigned char ch) {
    uint16_t ax;
    uint8_t ah, al;

    ah = 0x0;
    ah <<= 4;
    ah |= 0xf;
    ax = ah;
    ax <<= 8;
    al = ch;
    ax |= al;

    return ax;
}

void vga_set_cursor(int x, int y){
    uint16_t pos = y * vga_w + x;
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t) (pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void vga_enable_cursor(uint8_t cursor_start, uint8_t cursor_end) {
    outb(0x3D4, 0x0A);
    outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);

    outb(0x3D4, 0x0B);
    outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
}

void clear_vga_buffer(uint16_t **buffer) {
    vga_set_cursor(0, 0);
    for (uint32_t i = 0; i < VGA_SIZE; i++)
        (*buffer)[i] = vga_entry(0);
    next_line_index = 1;
    vga_index = 0;
    vga_set_cursor(0, 0);
}

void println() {
    if (next_line_index >= vga_h) {
        for (uint32_t i = 2; i < vga_index; i++)
            vga_buffer[i - vga_w] = vga_buffer[i];
        vga_index = next_line_index * vga_w;
    } else {
        vga_index = vga_w * next_line_index;
        next_line_index++;
    }

    vga_set_cursor(0, next_line_index);
}

void print_char(char ch) {
    if(ch=='\n') {
        println();
        return;
    }else if(ch=='\b') {
        vga_index--;
        vga_buffer[vga_index] = vga_entry(' ');
        return;
    }

    vga_buffer[vga_index] = vga_entry(ch);
    vga_index++;

    vga_set_cursor(vga_index, next_line_index);
}

void print_string(char *str) {
    uint32_t index = 0;
    while (str[index]) {
        print_char(str[index]);
        index++;
    }
}

void println_string(char *str) {
    uint32_t index = 0;
    while (str[index]) {
        print_char(str[index]);
        index++;
    }
    println();
}