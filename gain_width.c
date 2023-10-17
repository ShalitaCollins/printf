#include "main.h"

/**
 * determine_size - Evaluates the dimension to cast the argument
 * @formatted: Formatted string in which to print the arguments
 * @index: List of arguments to be printed.
 *
 * Return: Size.
 */
int determine_size(const char *formatted, int *index)
{
    int current_index = *index + 1;
    int size = 0;

    if (formatted[current_index] == 'l')
    {
        size = S_LONG;
    }
    else if (formatted[current_index] == 'h')
    {
        size = S_SHORT;
    }

    if (size == 0)
    {
        *index = current_index - 1;
    }
    else
    {
        *index = current_index;
    }

    return size;
}
