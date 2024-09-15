#ifndef STRING_H
#define STRING_H

#include "stdint.h"

void* memcpy(void* dest, const void* src, size_t count);
void* memset(void* dst, char value, size_t count);

void byte_swap(uint8_t *data, int len);

#endif //STRING_H
