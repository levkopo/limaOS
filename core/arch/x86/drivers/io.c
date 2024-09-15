#include <io.h>
#include <keyboardkeys.h>
#include <screen.h>

uint8_t read_port(uint16_t port) {
    unsigned char data;
    asm("in %%dx, %%al" : "=a" (data) : "d" (port));
    return data;
}

void write_port(uint16_t port, uint8_t data) {
    asm("out %%al, %%dx" : :"a" (data), "d" (port));
}

char getchar() {
    while(1) {
        uint8_t charKey = read_port(0x60);
        char key = getchar_keyboard(charKey).key;
        if(key!=' ') {
            write_port(0x60, 0);
            return key;
        }
    }
}

char* readline() {
    char* output = "";
    while (1) {
        char char_ = getchar();
        if(char_=='\n') {
            break;
        }

        print_char(char_);
        if(char_!='\b')
            output = appendCharToCharArray(output, char_);
    }

    println();
    return output;
}

void outb(unsigned short port, unsigned char value) {
    __asm__ volatile ( "outb %b0, %w1" : : "a"(value), "Nd"(port) : "memory");
}

unsigned char inb(unsigned short int port) {
    unsigned char _v;
    __asm__ __volatile__ ("inb %w1,%0" : "=a" (_v): "Nd" (port));
    return _v;
}

void play_sound(uint32_t nFrequency) {
    if (nFrequency == 0) {
        char tmp = (read_port(0x61) & 0xFC);
        write_port(0x61, tmp);
        return;
    }
    int Div;
    char tmp;

    //Set the PIT to the desired frequency
    Div = 1193180 / nFrequency;
    write_port(0x43, 0xb6);
    write_port(0x42, (uint8_t) (Div));
    write_port(0x42, (uint8_t) (Div >> 8));

    //And play the sound using the PC speaker
    tmp = read_port(0x61);
    if (tmp != (tmp | 3))
        write_port(0x61, tmp | 3);
}

void msleep(uint32_t millis) {
    asm("nop");
}