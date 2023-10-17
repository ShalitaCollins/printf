#include "main.h"

/**
 * obtain_format_flags - Determines active format_flags
 * @formatted: Formatted string to print the arguments
 * @index: Take a parameter.
 * Return: Flags:
 */
int obtain_format_flags(const char *formatted, int *index)
{
    /* - + 0 # ' ' */
    /* 1 2 4 8  16 */
    int j, current_index;
    int flags = 0;
    const char FLAGS_CHARS[] = {'-', '+', '0', '#', ' ', '\0'};
    const int FLAGS_ARRAY[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

    for (current_index = *index + 1; formatted[current_index] != '\0'; current_index++)
    {
        for (j = 0; FLAGS_CHARS[j] != '\0'; j++)
        {
            if (formatted[current_index] == FLAGS_CHARS[j])
            {
                flags |= FLAGS_ARRAY[j];
                break;
            }
        }

        if (FLAGS_CHARS[j] == 0)
        {
            break;
        }
    }

    *index = current_index - 1;

    return flags;
}
