#include "main.h"

int handle_write_char(char c, char buffer[], int flags, int width, int precision, int size);
int handle_write_number(int is_negative, int i, char buffer[], int flags, int width, int precision, int size);
long int convert_size_number(long int n, int size);

// Define F_MINUS flag here or include the appropriate header where it's defined
#define F_MINUS (1 << 0)
#define UNUSED(x) (void)(x)

int print_char(va_list types, char buffer[],
    int flags, int width, int precision, int size)
{
    char c = va_arg(types, int);
    return (handle_write_char(c, buffer, flags, width, precision, size));
}

int print_string(va_list types, char buffer[],
    int flags, int width, int precision, int size)
{
    int length = 0, i;
    char *str = va_arg(types, char *);

    if (str == NULL)
    {
        str = "(null)";
        if (precision >= 6)
            str = "      ";
    }

    if (str != NULL)
    {
        while (str[length] != '\0')
            length++;
    }

    if (precision >= 0 && precision < length)
        length = precision;

    if (width > length)
    {
        // Add a check for F_MINUS flag here
        if (flags & F_MINUS)
        {
            write(1, &str[0], length);
            for (i = width - length; i > 0; i--)
                write(1, " ", 1);
            return (width);
        }
        else
        {
            for (i = width - length; i > 0; i--)
                write(1, " ", 1);
            write(1, &str[0], length);
            return (width);
        }
    }

    if (str != NULL)
        return (write(1, str, length));
    else
        return 0;
}

// Rest of the code remains the same
