//
// Created by levkopo on 18.12.2021.
//

#ifndef KEYBOARDKEYS_H
#define KEYBOARDKEYS_H

#include <stdlib.h>

struct KeyboardKey {
    int code;
    bool up;
    char key;
};

struct KeyboardKey getchar_keyboard(int code) {
    struct KeyboardKey key;
    key.code = code;
    key.key = ' ';

    switch (code) {
        case 14: key.key = '\b'; break;
        case 16: key.key = 'q'; break;
        case 17: key.key = 'w'; break;
        case 18: key.key = 'e'; break;
        case 19: key.key = 'r'; break;
        case 20: key.key = 't'; break;
        case 21: key.key = 'y'; break;
        case 22: key.key = 'u'; break;
        case 23: key.key = 'i'; break;
        case 24: key.key = 'o'; break;
        case 25: key.key = 'p'; break;
        case 28: key.key = '\n'; break;
        case 30: key.key = 'a'; break;
        case 31: key.key = 's'; break;
        case 32: key.key = 'd'; break;
        case 33: key.key = 'f'; break;
        case 34: key.key = 'g'; break;
        case 35: key.key = 'h'; break;
        case 36: key.key = 'j'; break;
        case 37: key.key = 'k'; break;
        case 38: key.key = 'l'; break;
        case 39: key.key = ';'; break;
        case 40: key.key = '\''; break;
        case 44: key.key = 'z'; break;
        case 45: key.key = 'x'; break;
        case 46: key.key = 'c'; break;
        case 47: key.key = 'v'; break;
        case 48: key.key = 'b'; break;
        case 49: key.key = 'n'; break;
        case 50: key.key = 'm'; break;
        case 51: key.key = ','; break;
        case 52: key.key = '.'; break;
        case 53: key.key = '/'; break;
    }

    return key;
}
#endif //KEYBOARDKEYS_H
