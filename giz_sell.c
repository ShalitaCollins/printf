#include "main.h"

/**
 * giz_sell - Calculates the size to cast the argument
 * @format: Formatted string in which to print the arguments
 * @i: List of arguments to be printed.
 *
 * Return: Precision.
 */
int giz_sell(const char *format, int *i)
{
    int curr_i = *i + 1;
    int sell = 0;

    switch (format[curr_i]) {
        case 'l':
            sell= S_LONG;
            break;
        case 'h':
            sell = S_SHORT;
            break;
        default:
            *i = curr_i - 1;
    }

    if (sell != 0) {
        *i = curr_i;
    }

    return sell;
}
