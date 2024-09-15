#include <string.h>

void* memcpy(void* dst, const void* src, size_t count) {
    while (count-- > 0)
        ((char*) dst)[count] = ((char*) src)[count];
    return dst;
}

void* memset(void* dst, char value, size_t count) {
    while (count-- > 0)
        ((char*) dst)[count] = value;
    return dst;
}

void byte_swap(uint8_t *data, int len) {
    int i;
    uint8_t temp;
    for(i = 0; i < len; i += 2) {
        temp = data[i];
        data[i] = data[i+1];
        data[i+1] = temp;
    }
}