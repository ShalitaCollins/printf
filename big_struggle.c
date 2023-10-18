#include "main.h"
#include <stdarg.h>  // Include <stdarg.h> for va_list
#include <unistd.h>  // Include <unistd.h> for write

/**
 * _printf - A simple custom printf function
 * @format: The format string
 * @...: Variable arguments
 *
 * Return: Number of characters printed.
 */
int _printf(const char *format, ...)
{
    int count = 0;
    va_list args;

    if (format == NULL)
        return (-1);

    va_start(args, format);

    while (*format)
    {
        if (*format == '%')  // Check for format specifier
        {
            format++; // Move to the character after '%'
            if (*format == '\0') // If '%' is the last character, exit loop
                break;

            if (*format == 'c')  // Handle 'c' specifier
            {
                char c = va_arg(args, int); // Get character from va_list
                write(1, &c, 1); // Print the character
                count++;
            }
            else if (*format == 's')  // Handle 's' specifier
            {
                char *str = va_arg(args, char *); // Get string from va_list
                if (str == NULL)
                    str = "(null)"; // Handle NULL strings
                count += write(1, str, strlen(str)); // Print the string
            }
            else if (*format == '%')  // Handle '%%' specifier
            {
                write(1, "%", 1); // Print a single '%'
                count++;
            }
        }
        else  // Print regular characters
        {
            write(1, format, 1);
            count++;
        }

        format++; // Move to the next character in the format string
    }

    va_end(args); // Clean up the va_list

    return count;
}

int main(void)
{
    _printf("Hello %c, this is a %s example: %% and a number: %d\n", 'W', "printf", 42);
    return (0);
}
