#include "main.h"

/**
 * determine_precision - Evaluates the precision for printing
 * @formatted: Formatted string in which to print the arguments
 * @index: List of arguments to be printed.
 * @args_list: List of arguments.
 *
 * Return: Precision.
 */
int determine_precision(const char *formatted, int *index, va_list args_list)
{
    int current_index = *index + 1;
    int precision = -1;

    if (formatted[current_index] != '.')
    {
        return precision;
    }

    precision = 0;

    for (current_index += 1; formatted[current_index] != '\0'; current_index++)
    {
        if (is_digit(formatted[current_index]))
        {
            precision *= 10;
            precision += formatted[current_index] - '0';
        }
        else if (formatted[current_index] == '*')
        {
            current_index++;
            precision = va_arg(args_list, int);
            break;
        }
        else
        {
            break;
        }
    }

    *index = current_index - 1;

    return precision;
}
