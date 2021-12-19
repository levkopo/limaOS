#ifndef STDLIB_H
#define STDLIB_H

#include "stdint.h"
#include "stdbool.h"

#define VGA_ADDRESS 0xB8000

#define min(a, b) (((a) > (b)) ? (b) : (a))
#define max(a, b) (((a) > (b)) ? (a) : (b))

typedef struct { int quot; int rem; } div_t;
typedef struct { long quot; long rem; } ldiv_t;
static char *itoa_simple_helper(char *dest, int i);
char *itoa(char *dest, int i);
int atoi(char*);
int32_t abs(int32_t);
int64_t labs(int64_t);
size_t strlen(const char* str);
char* strcpy(char *dest, const char *src);
char* appendCharToCharArray(char* array, char a);
int strcmp(const char *p1, const char *p2);


//div_t div(int num, int denom); TODO:
//ldiv_t ldiv(long int num, long int denom); TODO:

//class std {
//    static:
//    int* nullptr = *ptr(0)
//}

void block();
#endif //STDLIB_H