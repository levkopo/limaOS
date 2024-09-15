//
// Created by levkopo on 07.04.24.
//

#ifndef LIMAOS_STDIO_H
#define LIMAOS_STDIO_H

struct FILE {
    char* _IO_write_base;
    char* _IO_write_ptr;
    char* _IO_write_end;
};

const int EOF = -1;

char *strerror(int num);
char *_strerror(const char *str);

struct FILE stdin;
struct FILE stdout;
struct FILE stderr;

#endif //LIMAOS_STDIO_H
