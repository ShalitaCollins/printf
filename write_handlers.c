#include "main.h"

/**
 * is_displayable - Checks if a character is displayable
 * @character: Character to be evaluated.
 *
 * Return: 1 if the character is displayable, 0 otherwise.
 */
int is_displayable(char character)
{
	if (character >= 32 && character < 127)
		return 1;

	return 0;
}

/**
 * add_hex_code - Appends ASCII in hexadecimal code to the buffer
 * @buffer: Array of characters.
 * @index: Index at which to start appending.
 * @ascii_code: ASCII code.
 * Return: Always 3.
 */
int add_hex_code(char ascii_code, char buffer[], int index)
{
	char code_map[] = "0123456789ABCDEF";
	/* The hexadecimal format code is always 2 digits long */
	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[index++] = '\\';
	buffer[index++] = 'x';

	buffer[index++] = code_map[ascii_code / 16];
	buffer[index] = code_map[ascii_code % 16];

	return 3;
}

/**
 * is_number - Checks if a character is a digit
 * @character: Character to be evaluated.
 *
 * Return: 1 if the character is a digit, 0 otherwise.
 */
int is_number(char character)
{
	if (character >= '0' && character <= '9')
		return 1;

	return 0;
}

/**
 * adjust_size_number - Casts a number to the specified size
 * @number: Number to be cast.
 * @size: Number indicating the type to cast to.
 *
 * Return: Casted value of number.
 */
long int adjust_size_number(long int number, int size)
{
	if (size == S_LONG)
		return number;
	else if (size == S_SHORT)
		return (short)number;

	return (int)number;
}

/**
 * adjust_size_unsigned - Casts an unsigned number to the specified size
 * @number: Number to be cast.
 * @size: Number indicating the type to cast to.
 *
 * Return: Casted value of number.
 */
long int adjust_size_unsigned(unsigned long int number, int size)
{
	if (size == S_LONG)
		return number;
	else if (size == S_SHORT)
		return (unsigned short)number;

	return (unsigned int)number;
}
