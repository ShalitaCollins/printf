#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "main.h"
int _printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    
    const char *ptr = format;
    while (*ptr != '\0') {
        if (*ptr == '%') {
            ptr++;
            switch (*ptr++) {
                case 'c': {
            
                    char ch = (char)va_arg(args, int);
                    putchar(ch);
                    break;
                }
                case 's': {
            
                    const char *str = va_arg(args, const char *);
                    puts(str);
                    break;
                }
                case '%': {
            
                    putchar('%');
                    break;
                }
                default: {
            
                    break;
                }
            }
        } else {
            
            putchar(*ptr++);
        }
    }

    va_end(args);
    return 0;
}
