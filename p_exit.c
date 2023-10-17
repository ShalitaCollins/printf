#include "main.h"

/************************* PRINT POSITIVE NUMBER *************************/

/**
 * print_positive - Prints a positive number
 * @args: List of arguments
 * @output: Output array to handle print
 * @format_flags: Calculates active format_flags
 * @format_width: Get width
 * @format_precision: Precision specification
 * @format_size: Size specifier
 * Return: Number of chars printed
 */
int print_positive(va_list args, char output[],
	int format_flags, int format_width, int format_precision, int format_size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(args, unsigned long int);

	num = convert_size_positive(num, format_size);

	if (num == 0)
		output[i--] = '0';

	output[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		output[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_positive(0, i, output, format_flags, format_width, format_precision, format_size));
}

/************* PRINT POSITIVE NUMBER IN OCTAL  ****************/

/**
 * print_octal - Prints an unsigned number in octal notation
 * @args: List of arguments
 * @output: Output array to handle print
 * @format_flags: Calculates active format_flags
 * @format_width: Get width
 * @format_precision: Precision specification
 * @format_size: Size specifier
 * Return: Number of chars printed
 */
int print_octal(va_list args, char output[],
	int format_flags, int format_width, int format_precision, int format_size)
{

	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(args, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(format_width);

	num = convert_size_positive(num, format_size);

	if (num == 0)
		output[i--] = '0';

	output[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		output[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (format_flags & F_HASH && init_num != 0)
		output[i--] = '0';

	i++;

	return (write_positive(0, i, output, format_flags, format_width, format_precision, format_size));
}

/************** PRINT POSITIVE NUMBER IN HEXADECIMAL **************/

/**
 * print_hexadecimal - Prints a positive number in hexadecimal notation
 * @args: List of arguments
 * @output: Output array to handle print
 * @format_flags: Calculates active format_flags
 * @format_width: Get width
 * @format_precision: Precision specification
 * @format_size: Size specifier
 * Return: Number of chars printed
 */
int print_hexadecimal(va_list args, char output[],
	int format_flags, int format_width, int format_precision, int format_size)
{
	return (print_hexa(args, "0123456789abcdef", output,
		format_flags, 'x', format_width, format_precision, format_size));
}

/************* PRINT POSITIVE NUMBER IN UPPER HEXADECIMAL **************/

/**
 * print_hexa_upper - Prints a positive number in upper hexadecimal notation
 * @args: List of arguments
 * @output: Output array to handle print
 * @format_flags: Calculates active format_flags
 * @format_width: Get width
 * @format_precision: Precision specification
 * @format_size: Size specifier
 * Return: Number of chars printed
 */
int print_hexa_upper(va_list args, char output[],
	int format_flags, int format_width, int format_precision, int format_size)
{
	return (print_hexa(args, "0123456789ABCDEF", output,
		format_flags, 'X', format_width, format_precision, format_size));
}

/************** PRINT HEXA NUMBER IN LOWER OR UPPER **************/

/**
 * print_hexa - Prints a hexadecimal number in lower or upper
 * @args: List of arguments
 * @map_to: Array of values to map the number to
 * @output: Output array to handle print
 * @format_flags: Calculates active format_flags
 * @flag_ch: Calculates active format_flags
 * @format_width: Get width
 * @format_precision: Precision specification
 * @format_size: Size specifier
 * Return: Number of chars printed
 */
int print_hexa(va_list args, char map_to[], char output[],
	int format_flags, char flag_ch, int format_width, int format_precision, int format_size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(args, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(format_width);

	num = convert_size_positive(num, format_size);

	if (num == 0)
		output[i--] = '0';

	output[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		output[i--] = map_to[num % 16];
		num /= 16;
	}

	if (format_flags & F_HASH && init_num != 0)
	{
		output[i--] = flag_ch;
		output[i--] = '0';
	}

	i++;

	return (write_positive(0, i, output, format_flags, format_width, format_precision, format_size));
}
