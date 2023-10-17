#include "main.h"

int print_pointer(va_list types, char buffer[], int flags, int width, int precision, int size)
{
    char extra_c = 0, padd = ' ';
    int ind = BUFF_SIZE - 2, length = 2; /* length=2, for '0x' */
    unsigned long num_addrs;
    void *addrs = va_arg(types, void *);

    if (addrs == NULL)
        return write(1, "(nil)", 5);

    buffer[BUFF_SIZE - 1] = '\0';

    num_addrs = (unsigned long)addrs;

    while (num_addrs > 0)
    {
        buffer[ind--] = "0123456789abcdef"[num_addrs % 16];
        num_addrs /= 16;
        length++;
    }

    if ((flags & F_ZERO) && !(flags & F_MINUS))
        padd = '0';
    if (flags & (F_PLUS | F_SPACE))
    {
        extra_c = flags & F_PLUS ? '+' : ' ';
        length++;
    }

    ind++;

    return write_pointer(buffer, ind, length, width, flags, padd, extra_c, 1);
}

int print_non_printable(va_list types, char buffer[], int flags, int width, int precision, int size)
{
    int i = 0, offset = 0;
    char *str = va_arg(types, char *);

    if (str == NULL)
        return write(1, "(null)", 6);

    while (str[i] != '\0')
    {
        if (is_printable(str[i]))
            buffer[i + offset] = str[i];
        else
            offset += append_hexa_code(str[i], buffer, i + offset);

        i++;
    }

    buffer[i + offset] = '\0';

    return write(1, buffer, i + offset);
}

int print_reverse(va_list types, char buffer[], int flags, int width, int precision, int size)
{
    char *str = va_arg(types, char *);
    int count = 0;

    if (str == NULL)
        str = ")Null(";

    for (int i = 0; str[i]; i++) { /* Find the length of the string */
        count++;
    }

    for (int i = count - 1; i >= 0; i--) {
        write(1, &str[i], 1);
    }

    return count;
}

int print_rot13string(va_list types, char buffer[], int flags, int width, int precision, int size)
{
    char x;
    char *str = va_arg(types, char *);
    int count = 0;

    if (str == NULL)
        str = "(AHYY)";

    for (unsigned int i = 0; str[i]; i++) {
        char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";
        unsigned int j;

        for (j = 0; in[j]; j++) {
            if (in[j] == str[i]) {
                x = out[j];
                write(1, &x, 1);
                count++;
                break;
            }
        }

        if (!in[j]) {
            x = str[i];
            write(1, &x, 1);
            count++;
        }
    }

    return count;
}
