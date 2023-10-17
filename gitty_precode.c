#include "main.h"

int gitty_precode(const char *format, int *i, va_list list)
{
    int curr_i = *i + 1;
    int precode = -1;

    if (format[curr_i] != '.')
        return precode;

    precode = 0;
    curr_i++;

    while (is_digit(format[curr_i]))
    {
        precode = precode * 10 + (format[curr_i] - '0');
        curr_i++;
    }

    if (format[curr_i] == '*')
    {
        curr_i++;
        precode = va_arg(list, int);
    }

    *i = curr_i - 1;

    return precode;
}
