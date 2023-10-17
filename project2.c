#include "main.h"

/************************* PRINT CHAR *************************/
int print_char(va_list types)
{
    char c = va_arg(types, int);
    return handle_write_char(c);
}

// PRINT A STRING
int print_string(va_list types)
{
    char *str = va_arg(types, char *);
    if (str == NULL)
        str = "(null)";

    int length = 0;
    while (str[length] != '\0')
        length++;

    return write(1, str, length);
}

//PRINT PERCENT SIGN
int print_percent()
{
    return write(1, "%%", 1);
}

// PRINT INT
int print_int(va_list types)
{
    long int n = va_arg(types, long int);
    n = convert_size_number(n);
    
    char buffer[BUFF_SIZE];
    int i = BUFF_SIZE - 2;
    int is_negative = 0;
    unsigned long int num = n;

    if (n == 0)
        buffer[i--] = '0';

    buffer[BUFF_SIZE - 1] = '\0';

    if (n < 0)
    {
        num = (unsigned long int)((-1) * n);
        is_negative = 1;
    }

    while (num > 0)
    {
        buffer[i--] = (num % 10) + '0';
        num /= 10;
    }

    i++;

    return write_number(is_negative, i, buffer);
}

// PRINT BINARY
int print_binary(va_list types)
{
    unsigned int n = va_arg(types, unsigned int);
    unsigned int a[32];
    int count = 0;

    for (int i = 0, m = 2147483648; i < 32; i++)
    {
        a[i] = (n / m) % 2;
        m /= 2;
    }

    for (int i = 0, sum = 0; i < 32; i++)
    {
        sum += a[i];
        if (sum || i == 31)
        {
            char z = '0' + a[i];
            write(1, &z, 1);
            count++;
        }
    }

    return count;
}
