#include "main.h"

/************************* PRINT CHAR *************************/

/**
 * print_character - Prints a character
 * @types: List of arguments
 * @output: Output array to handle print
 * @format_flags: Calculates active format_flags
 * @format_width: Width
 * @format_precision: Precision specification
 * @format_size: Size specifier
 * Return: Number of characters printed
 */
int print_character(va_list types, char output[],
	int format_flags, int format_width, int format_precision, int format_size)
{
	char c = va_arg(types, int);

	return (write_character(c, output, format_flags, format_width, format_precision, format_size));
}
/************************* PRINT A STRING *************************/
/**
 * print_string - Prints a string
 * @types: List of arguments
 * @output: Output array to handle print
 * @format_flags: Calculates active format_flags
 * @format_width: Get width.
 * @format_precision: Precision specification
 * @format_size: Size specifier
 * Return: Number of characters printed
 */
int print_string(va_list types, char output[],
	int format_flags, int format_width, int format_precision, int format_size)
{
	int length = 0, i;
	char *str = va_arg(types, char *);

	UNUSED(output);
	UNUSED(format_flags);
	UNUSED(format_width);
	UNUSED(format_precision);
	UNUSED(format_size);
	if (str == NULL)
	{
		str = "(null)";
		if (format_precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (format_precision >= 0 && format_precision < length)
		length = format_precision;

	if (format_width > length)
	{
		if (format_flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (i = format_width - length; i > 0; i--)
				write(1, " ", 1);
			return (format_width);
		}
		else
		{
			for (i = format_width - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (format_width);
		}
	}

	return (write(1, str, length));
}
/************************* PRINT PERCENT SIGN *************************/
/**
 * print_percent - Prints a percent sign
 * @types: List of arguments
 * @output: Output array to handle print
 * @format_flags: Calculates active format_flags
 * @format_width: Get width.
 * @format_precision: Precision specification
 * @format_size: Size specifier
 * Return: Number of characters printed
 */
int print_percent(va_list types, char output[],
	int format_flags, int format_width, int format_precision, int format_size)
{
	UNUSED(types);
	UNUSED(output);
	UNUSED(format_flags);
	UNUSED(format_width);
	UNUSED(format_precision);
	UNUSED(format_size);
	return (write(1, "%%", 1));
}

/************************* PRINT INT *************************/
/**
 * print_integer - Print integer
 * @types: List of arguments
 * @output: Output array to handle print
 * @format_flags: Calculates active format_flags
 * @format_width: Get width.
 * @format_precision: Precision specification
 * @format_size: Size specifier
 * Return: Number of characters printed
 */
int print_integer(va_list types, char output[],
	int format_flags, int format_width, int format_precision, int format_size)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, format_size);

	if (n == 0)
		output[i--] = '0';

	output[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		output[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_number(is_negative, i, output, format_flags, format_width, format_precision, format_size));
}

/************************* PRINT BINARY *************************/
/**
 * print_binary - Prints an unsigned number
 * @types: List of arguments
 * @output: Output array to handle print
 * @format_flags: Calculates active format_flags
 * @format_width: Get width.
 * @format_precision: Precision specification
 * @format_size: Size specifier
 * Return: Number of characters printed.
 */
int print_binary(va_list types, char output[],
	int format_flags, int format_width, int format_precision, int format_size)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	UNUSED(output);
	UNUSED(format_flags);
	UNUSED(format_width);
	UNUSED(format_precision);
	UNUSED(format_size);

	n = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
