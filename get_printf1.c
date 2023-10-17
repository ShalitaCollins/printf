#include "main.h"

/****************** PRINT MEMORY_LOCATION ******************/

/**
 * print_memory_location - Prints the value of a memory location
 * @args: List of arguments
 * @output: Output array to handle print
 * @format_flags: Calculates active format_flags
 * @format_width: Get width
 * @format_precision: Precision specification
 * @format_size: Size specifier
 * Return: Number of chars printed.
 */
int print_memory_location(va_list args, char output[],
    int format_flags, int format_width, int format_precision, int format_size)
{
    char extra_c = 0, padding = ' ';
    int index = BUFF_SIZE - 2, length = 2, padding_start = 1; /* length=2, for '0x' */
    unsigned long address;
    char mapping[] = "0123456789abcdef";
    void *ptr = va_arg(args, void *);

    UNUSED(format_width);
    UNUSED(format_size);

    if (ptr == NULL)
        return write(1, "(nil)", 5);

    output[BUFF_SIZE - 1] = '\0';
    UNUSED(format_precision);

    address = (unsigned long)ptr;

    while (address > 0)
    {
        output[index--] = mapping[address % 16];
        address /= 16;
        length++;
    }

    if ((format_flags & F_ZERO) && !(format_flags & F_MINUS))
        padding = '0';
    if (format_flags & F_PLUS)
        extra_c = '+', length++;
    else if (format_flags & F_SPACE)
        extra_c = ' ', length++;

    index++;

    return print_memory_location(output, index, length,
        format_width, format_flags, padding, extra_c, padding_start);
}

/****************** PRINT UNPRINTABLE ******************/

/**
 * print_unprintable - Prints ascii codes in hexa of unprintable characters
 * @args: List of arguments
 * @output: Output array to handle print
 * @format_flags: Calculates active format_flags
 * @format_width: Get width
 * @format_precision: Precision specification
 * @format_size: Size specifier
 * Return: Number of chars printed
 */
int print_unprintable(va_list args, char output[],
    int format_flags, int format_width, int format_precision, int format_size)
{
    int i = 0, offset = 0;
    char *str = va_arg(args, char *);

    UNUSED(format_flags);
    UNUSED(format_width);
    UNUSED(format_precision);
    UNUSED(format_size);

    if (str == NULL)
        return write(1, "(null)", 6);

    while (str[i] != '\0')
    {
        if (is_printable(str[i]))
            output[i + offset] = str[i];
        else
            offset += append_hexa_code(str[i], output, i + offset);

        i++;
    }

    output[i + offset] = '\0';

    return write(1, output, i + offset);
}

/****************** PRINT ESREVER ******************/

/**
 * print_esrever - Prints the reverse of a string.
 * @args: List of arguments
 * @output: Output array to handle print
 * @format_flags: Calculates active format_flags
 * @format_width: Get width
 * @format_precision: Precision specification
 * @format_size: Size specifier
 * Return: Numbers of chars printed
 */

int print_esrever(va_list args, char output[],
    int format_flags, int format_width, int format_precision, int format_size)
{
    char *str;
    int i, count = 0;

    UNUSED(output);
    UNUSED(format_flags);
    UNUSED(format_width);
    UNUSED(format_size);

    str = va_arg(args, char *);

    if (str == NULL)
    {
        UNUSED(format_precision);
        str = ")Null(";
    }

    for (i = 0; str[i]; i++);

    for (i = i - 1; i >= 0; i--)
    {
        char z = str[i];
        write(1, &z, 1);
        count++;
    }

    return count;
}

/****************** PRINT ROT13_STRING ******************/

/**
 * print_rot13_string - Print a string in ROT13.
 * @args: List of arguments
 * @output: Output array to handle print
 * @format_flags: Calculates active format_flags
 * @format_width: Get width
 * @format_precision: Precision specification
 * @format_size: Size specifier
 * Return: Numbers of chars printed
 */
int print_rot13_string(va_list args, char output[],
    int format_flags, int format_width, int format_precision, int format_size)
{
    char x;
    char *str;
    unsigned int i, j;
    int count = 0;
    char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

    str = va_arg(args, char *);
    UNUSED(output);
    UNUSED(format_flags);
    UNUSED(format_width);
    UNUSED(format_precision);
    UNUSED(format_size);

    if (str == NULL)
        str = "(AHYY)";
    for (i = 0; str[i]; i++)
    {
        for (j = 0; in[j]; j++)
        {
            if (in[j] == str[i])
            {
                x = out[j];
                write(1, &x, 1);
                count++;
                break;
            }
        }
        if (!in[j])
        {
            x = str[i];
            write(1, &x, 1);
            count++;
        }
    }
    return count;
}
