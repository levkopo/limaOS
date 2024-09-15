//
// Created by levkopo on 07.04.24.
//

#include <stdio.h>

const int ERR_NO = 0;
const int ERR_NOT_FOUND = 1;

void init_stdio() {
}


char *strerror(int num) {
    if(num == ERR_NOT_FOUND) {
        return "Not found";
    }

    return "";
}

char *_strerror(const char *str) {

}