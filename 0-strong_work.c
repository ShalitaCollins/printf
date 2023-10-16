#include <stdio.h>
#include <stdarg.h>
#include "main.h" 
int _printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    int char_count = 0;

    while (*format) {
        if (*format != '%') {
            putchar(*format);
            char_count++;
        } else {
            format++;
            if (*format == '\0') break;

            if (*format == 'c') {
                char c = va_arg(args, int);
                putchar(c);
                char_count++;
            } else if (*format == 's') {
                char *str = va_arg(args, char *);
                if (str != NULL) {
                    while (*str) {
                        putchar(*str);
                        str++;
                        char_count++;
                    }
                }
            } else if (*format == '%') {
                putchar('%');
                char_count++;
            } else {
                // Handle unsupported format specifiers
                putchar('%');
                putchar(*format);
                char_count += 2;
            }
        }
        format++;
    }

    va_end(args);
    return char_count;
}

int main() {
    int num = 42;
    char *str = "Hello, world!";

    int printed = _printf("This is a number: %d, a character: %c, a string: %s, and a percent sign: %%\n", num, 'A', str);
    printf("Characters printed: %d\n", printed);

    return 0;
}
