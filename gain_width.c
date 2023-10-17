#include "main.h"

/**
 * gain_width - Calculates the width for printing
 * @format: Formatted string in which to print the arguments.
 * @i: List of arguments to be printed.
 * @list: List of arguments.
 *
 * Return: Width.
 */
int get_width(const char *format, int *i, va_list list)
{
    int curr_i = *i + 1;
    int width = 0;

    while (is_digit(format[curr_i]))
    {
        width = width * 10 + (format[curr_i] - '0');
        curr_i++;
    }

    if (format[curr_i] == '*')
    {
        curr_i++;
        width = va_arg(list, int);
    }

    *i = curr_i - 1;

    return width;
}
