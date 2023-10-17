#include "main.h"

/**
 * determine_width - Computes the breadth for printing
 * @formatted: Formatted string in which to print the arguments.
 * @index: List of arguments to be printed.
 * @list: List of arguments.
 *
 * Return: Breadth.
 */
int determine_width(const char *formatted, int *index, va_list list)
{
    int current_index;
    int breadth = 0;

    for (current_index = *index + 1; formatted[current_index] != '\0'; current_index++)
    {
        if (is_digit(formatted[current_index]))
        {
            breadth *= 10;
            breadth += formatted[current_index] - '0';
        }
        else if (formatted[current_index] == '*')
        {
            current_index++;
            breadth = va_arg(list, int);
            break;
        }
        else
        {
            break;
        }
    }

    *index = current_index - 1;

    return breadth;
}
