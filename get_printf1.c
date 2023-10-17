#include "main.h"
#include <string.h>
/**
 * get_flags - Calculates active flags
 * @format: Formatted string in which to print the arguments
 * @i: Current position in the format string
 * Return: Flags:
 */
int get_flags(const char *format, int *i)
{
    const char* FLAGS_CH = "-+0# ";
    const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE};
    int flags = 0;
    int curr_i = *i + 1;

    while (format[curr_i] != '\0') {
        char current_char = format[curr_i];
        const char* flag_ptr = strchr(FLAGS_CH, current_char);
        
        if (flag_ptr == NULL) {
            break; // No more flags found
        }

        int flag_index = flag_ptr - FLAGS_CH;
        flags |= FLAGS_ARR[flag_index];
        curr_i++;
    }

    *i = curr_i - 1;
    return flags;
}
