#include "include/screen.h"

uint16_t* vga_buffer = (uint16_t*) VGA_ADDRESS;
uint8_t vga_w = 80;
uint8_t vga_h = 25;
uint32_t vga_index, next_line_index = 1;

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
    uint16_t pos = y * vga_w + x + 1;
//    outb(0x3D4, 0x0F);
//    outb(0x3D5, (uint8_t) (pos & 0xFF));
//    outb(0x3D4, 0x0E);
//    outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void clear_vga_buffer(uint16_t **buffer) {
    vga_set_cursor(0, 0);
    for (uint32_t i = 0; i < VGA_SIZE; i++)
        (*buffer)[i] = vga_entry(0);
    next_line_index = 1;
    vga_index = 0;
}

void init_vga(void) {
    clear_vga_buffer(&vga_buffer);
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