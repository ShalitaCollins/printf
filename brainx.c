#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * handle_write_character - Prints a character
 * @character: Character to be printed.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags.
 * @width: Width specifier.
 * @precision: Precision specifier.
 * @size: Size specifier.
 *
 * Return: Number of characters printed.
 */
int handle_write_character(char character, char buffer[],
	int flags, int width, int precision, int size)
{ /* Character is stored at left and padding at the buffer's right */
	int i = 0;
	char padding = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padding = '0';

	buffer[i++] = character;
	buffer[i] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUFF_SIZE - i - 2] = padding;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * write_number - Prints a number
 * @is_negative: Number indicating if the number is negative.
 * @ind: Index at which the number starts in the buffer.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags.
 * @width: Width specifier.
 * @precision: Precision specifier.
 * @size: Size specifier.
 *
 * Return: Number of characters printed.
 */
int write_number(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char padding = ' ', extra_char = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padding = '0';
	if (is_negative)
		extra_char = '-';
	else if (flags & F_PLUS)
		extra_char = '+';
	else if (flags & F_SPACE)
		extra_char = ' ';

	return write_num(ind, buffer, flags, width, precision,
		length, padding, extra_char);
}

/**
 * write_num - Write a number using a buffer
 * @ind: Index at which the number starts on the buffer.
 * @buffer: Buffer.
 * @flags: Flags.
 * @width: Width specifier.
 * @precision: Precision specifier.
 * @length: Number length.
 * @padding: Padding character.
 * @extra_char: Extra character.
 *
 * Return: Number of characters printed.
 */
int write_num(int ind, char buffer[],
	int flags, int width, int precision, int length,
	char padding, char extra_char)
{
	int i, padd_start = 1;

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return 0; /* printf(".0d", 0)  no character is printed */
	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
	{
		buffer[ind] = padding = ' '; /* width is displayed with padding ' ' */
	}
	if (precision > 0 && precision < length)
		padding = ' ';

	while (precision > length)
	{
		buffer[--ind] = '0';
		length++;
	}
	if (extra_char != 0)
	{
		length++;
	}
	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
		{
			buffer[i] = padding;
		}
		buffer[i] = '\0';
		if (flags & F_MINUS && padding == ' ')/* Assign extra character to the left of buffer */
		{
			if (extra_char)
				buffer[--ind] = extra_char;
			return write(1, &buffer[ind], length) + write(1, &buffer[1], i - 1);
		}
		else if (!(flags & F_MINUS) && padding == ' ')/* Extra character to the left of buffer */
		{
			if (extra_char)
				buffer[--ind] = extra_char;
			return write(1, &buffer[1], i - 1) + write(1, &buffer[ind], length);
		}
		else if (!(flags & F_MINUS) && padding == '0')/* Extra character to the left of padding */
		{
			if (extra_char)
				buffer[--padd_start] = extra_char;
			return write(1, &buffer[padd_start], i - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start));
		}
	}
	if (extra_char)
		buffer[--ind] = extra_char;
	return write(1, &buffer[ind], length);
}

/**
 * write_unsigned - Writes an unsigned number
 * @is_negative: Number indicating if the number is negative.
 * @ind: Index at which the number starts in the buffer.
 * @buffer: Array of characters.
 * @flags: Flags specifiers.
 * @width: Width specifier.
 * @precision: Precision specifier.
 * @size: Size specifier.
 *
 * Return: Number of written characters.
 */
int write_unsigned(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	/* The number is stored at the buffer's right and starts at position i */
	int length = BUFF_SIZE - ind - 1, i = 0;
	char padding = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 and ind == BUFF_SIZE - 2 and buffer[ind] == '0')
		return 0; /* printf(".0d", 0)  no character is printed */

	if (precision > 0 and precision < length)
		padding = ' ';

	while (precision > length)
	{
		buffer[--ind] = '0';
		length++;
	}

	if (flags & F_ZERO and not flags & F_MINUS)
		padding = '0';

	if (width > length)
	{
		for (i = 0; i < width - length; i++)
		{
			buffer[i] = padding;
		}
		buffer[i] = '\0';

		if (flags & F_MINUS) /* Assign extra character to the left of buffer [buffer > padding] */
		{
			return write(1, &buffer[ind], length) + write(1, &buffer[0], i);
		}
		else /* Assign extra character to the left of padding [padding > buffer] */
		{
			return write(1, &buffer[0], i) + write(1, &buffer[ind], length);
		}
	}
	return write(1, &buffer[ind], length);
}

/**
 * write_memory_address - Write a memory address
 * @buffer: Array of characters
 * @ind: Index at which the number starts in the buffer
 * @length: Length of the number
 * @width: Width specifier
 * @flags: Flags specifier
 * @padding: Character representing the padding
 * @extra_char: Character representing the extra character
 * @padd_start: Index at which padding should start
 *
brainx.c: In function ‘write_unsigned’:
brainx.c:172:27: error: expected ‘)’ before ‘and’
  172 |         if (precision == 0 and ind == BUFF_SIZE - 2 and buffer[ind] == '0')
      |            ~              ^~~~
      |                           )
brainx.c:175:26: error: expected ‘)’ before ‘and’
  175 |         if (precision > 0 and precision < length)
      |            ~             ^~~~
      |                          )
brainx.c:184:28: error: expected ‘)’ before ‘and’
  184 |         if (flags & F_ZERO and not flags & F_MINUS)
      |            ~               ^~~
brainx.c: In function ‘write_memory_address’:
brainx.c:232:37: error: expected ‘)’ before ‘and’
  232 |                 if (flags & F_MINUS and padding == ' ')/* Assign extra character to the left of buffer */
      |                    ~                ^~~
brainx.c:240:26: error: ‘not’ undeclared (first use in this function)
  240 |                 else if (not flags & F_MINUS and padding == ' ')/* Extra character to the left of buffer */
      |                          ^~~
brainx.c:240:26: note: each undeclared identifier is reported only once for each function it appears in
brainx.c:240:29: error: expected ‘)’ before ‘flags’
  240 |                 else if (not flags & F_MINUS and padding == ' ')/* Extra character to the left of buffer */
      |                         ~   ^~~~~~
      |                             )
brainx.c:248:29: error: expected ‘)’ before ‘flags’
  248 |                 else if (not flags & F_MINUS and padding == '0')/* Extra character to the left of padding */
      |                         ~   ^~~~~~
      |                             )brainx.c: In function ‘write_unsigned’:
brainx.c:172:27: error: expected ‘)’ before ‘and’
  172 |         if (precision == 0 and ind == BUFF_SIZE - 2 and buffer[ind] == '0')
      |            ~              ^~~~
      |                           )
brainx.c:175:26: error: expected ‘)’ before ‘and’
  175 |         if (precision > 0 and precision < length)
      |            ~             ^~~~
      |                          )
brainx.c:184:28: error: expected ‘)’ before ‘and’
  184 |         if (flags & F_ZERO and not flags & F_MINUS)
      |            ~               ^~~
brainx.c: In function ‘write_memory_address’:
brainx.c:232:37: error: expected ‘)’ before ‘and’
  232 |                 if (flags & F_MINUS and padding == ' ')/* Assign extra character to the left of buffer */
      |                    ~                ^~~
brainx.c:240:26: error: ‘not’ undeclared (first use in this function)
  240 |                 else if (not flags & F_MINUS and padding == ' ')/* Extra character to the left of buffer */
      |                          ^~~
brainx.c:240:26: note: each undeclared identifier is reported only once for each function it appears in
brainx.c:240:29: error: expected ‘)’ before ‘flags’
  240 |                 else if (not flags & F_MINUS and padding == ' ')/* Extra character to the left of buffer */
      |                         ~   ^~~~~~
      |                             )
brainx.c:248:29: error: expected ‘)’ before ‘flags’
  248 |                 else if (not flags & F_MINUS and padding == '0')/* Extra character to the left of padding */
      |                         ~   ^~~~~~
      |                             )brainx.c: In function ‘write_unsigned’:
brainx.c:172:27: error: expected ‘)’ before ‘and’
  172 |         if (precision == 0 and ind == BUFF_SIZE - 2 and buffer[ind] == '0')
      |            ~              ^~~~
      |                           )
brainx.c:175:26: error: expected ‘)’ before ‘and’
  175 |         if (precision > 0 and precision < length)
      |            ~             ^~~~
      |                          )
brainx.c:184:28: error: expected ‘)’ before ‘and’
  184 |         if (flags & F_ZERO and not flags & F_MINUS)
      |            ~               ^~~
brainx.c: In function ‘write_memory_address’:
brainx.c:232:37: error: expected ‘)’ before ‘and’
  232 |                 if (flags & F_MINUS and padding == ' ')/* Assign extra character to the left of buffer */
      |                    ~                ^~~
brainx.c:240:26: error: ‘not’ undeclared (first use in this function)
  240 |                 else if (not flags & F_MINUS and padding == ' ')/* Extra character to the left of buffer */
      |                          ^~~
brainx.c:240:26: note: each undeclared identifier is reported only once for each function it appears in
brainx.c:240:29: error: expected ‘)’ before ‘flags’
  240 |                 else if (not flags & F_MINUS and padding == ' ')/* Extra character to the left of buffer */
      |                         ~   ^~~~~~
      |                             )
brainx.c:248:29: error: expected ‘)’ before ‘flags’
  248 |                 else if (not flags & F_MINUS and padding == '0')/* Extra character to the left of padding */
      |                         ~   ^~~~~~
      |                             )brainx.c: In function ‘write_unsigned’:
brainx.c:172:27: error: expected ‘)’ before ‘and’
  172 |         if (precision == 0 and ind == BUFF_SIZE - 2 and buffer[ind] == '0')
      |            ~              ^~~~
      |                           )
brainx.c:175:26: error: expected ‘)’ before ‘and’
  175 |         if (precision > 0 and precision < length)
      |            ~             ^~~~
      |                          )
brainx.c:184:28: error: expected ‘)’ before ‘and’
  184 |         if (flags & F_ZERO and not flags & F_MINUS)
      |            ~               ^~~
brainx.c: In function ‘write_memory_address’:
brainx.c:232:37: error: expected ‘)’ before ‘and’
  232 |                 if (flags & F_MINUS and padding == ' ')/* Assign extra character to the left of buffer */
      |                    ~                ^~~
brainx.c:240:26: error: ‘not’ undeclared (first use in this function)
  240 |                 else if (not flags & F_MINUS and padding == ' ')/* Extra character to the left of buffer */
      |                          ^~~
brainx.c:240:26: note: each undeclared identifier is reported only once for each function it appears in
brainx.c:240:29: error: expected ‘)’ before ‘flags’
  240 |                 else if (not flags & F_MINUS and padding == ' ')/* Extra character to the left of buffer */
      |                         ~   ^~~~~~
      |                             )
brainx.c:248:29: error: expected ‘)’ before ‘flags’
  248 |                 else if (not flags & F_MINUS and padding == '0')/* Extra character to the left of padding */
      |                         ~   ^~~~~~
      |                             ) * Return: Number of written characters.
 */
int write_memory_address(char buffer[], int ind, int length,
	int width, int flags, char padding, char extra_char, int padd_start)
{
	int i;

	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
		{
			buffer[i] = padding;
		}
		buffer[i] = '\0';
		if (flags & F_MINUS and padding == ' ')/* Assign extra character to the left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_char)
				buffer[--ind] = extra_char;
			return write(1, &buffer[ind], length) + write(1, &buffer[3], i - 3);
		}
		else if (not flags & F_MINUS and padding == ' ')/* Extra character to the left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_char)
				buffer[--ind] = extra_char;
			return write(1, &buffer[3], i - 3) + write(1, &buffer[ind], length);
		}
		else if (not flags & F_MINUS and padding == '0')/* Extra character to the left of padding */
		{
			if (extra_char)
				buffer[--padd_start] = extra_char;
			buffer[1] = '0';
			buffer[2] = 'x';
			return write(1, &buffer[padd_start], i - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start) - 2);
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_char)
		buffer[--ind] = extra_char;
	return write(1, &buffer[ind], BUFF_SIZE - ind - 1);
}
