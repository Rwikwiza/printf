#include "main.h"

unsigned int print_c(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int print_percent(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int print_p(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);

/**
 * print_c - Converts an argument to an unsigned char
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @wid: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int print_c(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	char c;
	unsigned int retrn = 0;
	(void)prec;
	(void)len;
	c = va_arg(args, int);
	retrn += width_printer(output, retrn, flags, wid);
	retrn += _memcpy(output, &c, 1);
	retrn += neg_width_printer(output, retrn, flags, wid);
	return (retrn);
}

/**
 * print_percent - Stores a percent sign to a buffer
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @wid: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer (always 1).
 */

unsigned int print_percent(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	char percent = '%';
	unsigned int retrn = 0;
	(void)args;
	(void)prec;
	(void)len;
	retrn += width_printer(output, retrn, flags, wid);
	retrn += _memcpy(output, &percent, 1);
	retrn += neg_width_printer(output, retrn, flags, wid);
	return (retrn);
}

/**
 * print_p - Converts the address of an argument to hex and
 *             stores it to a buffer contained in a struct.
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @wid: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * @output: A buffer_t struct containing a character array..
 *
 * Return: The number of bytes stored to the buffer.
 */

unsigned int print_p(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	char *null = "(nil)";
	unsigned long int address;
	unsigned int retrn = 0;
	(void)len;
	address = va_arg(args, unsigned long int);
	if (address == '\0')
		return (_memcpy(output, null, 5));
	flags |= 32;
	retrn += convert_ubase(output, address, "0123456789abcdef", flags, wid, prec);
	retrn += neg_width_printer(output, retrn, flags, wid);
	return (retrn);
}
