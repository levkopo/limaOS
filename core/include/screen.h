#ifndef SCREEN_H
#define SCREEN_H

#include "stdlib.h"
#include <io.h>

enum VIDEO_TYPE
{
    VIDEO_TYPE_NONE = 0x00,
    VIDEO_TYPE_COLOUR = 0x20,
    VIDEO_TYPE_MONOCHROME = 0x30,
};

#define VGA_SIZE vga_w * vga_h

#define VIDEO_COLOUR_BLACK 0x000000
#define VIDEO_COLOUR_BLUE 0x0000AA
#define VIDEO_COLOUR_GREEN 0x00AA00
#define VIDEO_COLOUR_CYAN 0x00AAAA
#define VIDEO_COLOUR_RED 0xAA0000
#define VIDEO_COLOUR_PURPLE 0xAA00AA
#define VIDEO_COLOUR_GRAY 0xAAAAAA

extern enum VIDEO_TYPE video_type;
extern uint16_t* vga_buffer;
extern uint8_t vga_w;
extern uint8_t vga_h;
extern uint32_t vga_index, next_line_index;

uint16_t detect_bios_area_hardware(void);
enum VIDEO_TYPE get_bios_area_video_type(void);

uint16_t vga_entry(unsigned char ch);
void clear_vga_buffer(uint16_t **buffer);
void vga_enable_cursor(uint8_t cursor_start, uint8_t cursor_end);
void vga_init(void);
void println();
void print_char(char ch);
void print_string(char *str);
void println_string(char *str);

#endif //SCREEN_H