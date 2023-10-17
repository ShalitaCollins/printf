#include "main.h"

/**
 * execute_print - Outputs an argument based on its type
 * @formatted: Formatted string in which to print the arguments.
 * @args_list: List of arguments to be printed.
 * @index: Index.
 * @output_buffer: Buffer array to handle print.
 * @active_flags: Calculates active flags
 * @breadth: Get breadth.
 * @precision: Precision specification
 * @magnitude: Size specifier
 * Return: 1 or 2;
 */
int execute_print(const char *formatted, int *index, va_list args_list, char output_buffer[],
	int active_flags, int breadth, int precision, int magnitude)
{
	int i, unknown_length = 0, characters_printed = -1;
	fmt_t fmt_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};
	for (i = 0; fmt_types[i].fmt != '\0'; i++)
		if (formatted[*index] == fmt_types[i].fmt)
			return (fmt_types[i].fn(args_list, output_buffer, active_flags, breadth, precision, magnitude));

	if (fmt_types[i].fmt == '\0')
	{
		if (formatted[*index] == '\0')
			return (-1);
		unknown_length += write(1, "%%", 1);
		if (formatted[*index - 1] == ' ')
			unknown_length += write(1, " ", 1);
		else if (breadth)
		{
			--(*index);
			while (formatted[*index] != ' ' && formatted[*index] != '%')
				--(*index);
			if (formatted[*index] == ' ')
				--(*index);
			return (1);
		}
		unknown_length += write(1, &formatted[*index], 1);
		return (unknown_length);
	}
	return (characters_printed);
}
