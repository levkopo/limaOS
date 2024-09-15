#ifndef STDLIB_H
#define STDLIB_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define min(a, b) (((a) > (b)) ? (b) : (a))
#define max(a, b) (((a) > (b)) ? (a) : (b))

typedef struct { int quot; int rem; } div_t;
typedef struct { long quot; long rem; } ldiv_t;

void abort(void);
int abs(int n);
int at_quick_exit(void (*func)(void));
int atexit(void (*func)(void));

static char *itoa_simple_helper(char *dest, int i);
char *itoa(int n, char * buffer, int radix);
int atoi (const char * str);
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

#endif //STDLIB_H