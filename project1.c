#include "main.h"

void output_buffer(char buffer[], int *buffer_index);

/**
 * _printf - Custom printf function
 * @format: Format string.
 * Return: Number of characters printed.
 */
int _printf(const char *format, ...)
{
	int i, total_printed = 0, printed_chars = 0;
	int format_flags, format_width, format_precision, format_size, buffer_index = 0;
	va_list args;
	char output_buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(args, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			output_buffer[buffer_index++] = format[i];
			if (buffer_index == BUFF_SIZE)
				output_buffer(output_buffer, &buffer_index);
			/* write(1, &format[i], 1);*/
			printed_chars++;
		}
		else
		{
			output_buffer(output_buffer, &buffer_index);
			format_flags = get_format_flags(format, &i);
			format_width = get_format_width(format, &i, args);
			format_precision = get_format_precision(format, &i, args);
			format_size = get_format_size(format, &i);
			++i;
			total_printed = process_format(format, &i, args, output_buffer,
				format_flags, format_width, format_precision, format_size);
			if (total_printed == -1)
				return (-1);
			printed_chars += total_printed;
		}
	}

	output_buffer(output_buffer, &buffer_index);

	va_end(args);

	return (printed_chars);
}

/**
 * output_buffer - Prints the contents of the output buffer if it exists
 * @buffer: Array of characters.
 * @buffer_index: Index at which to add the next character, represents the length.
 */
void output_buffer(char buffer[], int *buffer_index)
{
	if (*buffer_index > 0)
		write(1, &buffer[0], *buffer_index);

	*buffer_index = 0;
}
