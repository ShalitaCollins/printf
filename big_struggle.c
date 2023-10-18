#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int _printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Iterate over the format string and process each conversion specifier
    const char *ptr = format;
    while (*ptr != '\0') {
        if (*ptr == '%') {
            ptr++;
            switch (*ptr++) {
                case 'c': {
                    // Handle the 'c' conversion specifier
                    char ch = (char)va_arg(args, int);
                    putchar(ch);
                    break;
                }
                case 's': {
                    // Handle the 's' conversion specifier
                    const char *str = va_arg(args, const char *);
                    puts(str);
                    break;
                }
                case '%': {
                    // Handle the '%' conversion specifier
                    putchar('%');
                    break;
                }
                default: {
                    // Unknown conversion specifier, ignore it
                    break;
                }
            }
        } else {
            // Output the literal character
            putchar(*ptr++);
        }
    }

    va_end(args);
    return 0;
}
