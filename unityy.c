#include "main.h"
#include <stdlib.h>
int is_printable(char c) {
    return (c >= 32 && c < 127);
}

int append_hexa_code(char ascii_code, char buffer[], int i) {
    const char map_to[] = "0123456789ABCDEF";
    buffer[i++] = '\\';
    buffer[i++] = 'x';
    buffer[i++] = map_to[abs(ascii_code) / 16];
    buffer[i] = map_to[abs(ascii_code) % 16];
    return 3;
}

int is_digit(char c) {
    return (c >= '0' && c <= '9');
}

long int convert_size_number(long int num, int size) {
    if (size == S_LONG) {
        return num;
    } else if (size == S_SHORT) {
        return (short)num;
    } else {
        return (int)num;
    }
}

long int convert_size_unsgnd(unsigned long int num, int size) {
    if (size == S_LONG) {
        return num;
    } else if (size == S_SHORT) {
        return (unsigned short)num;
    } else {
        return (unsigned int)num;
    }
}
