#include "main.h"

unsigned int print_x(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int print_X(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);

/**
 * print_x - Converts an unsigned int argument to hex using abcdef
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @wid: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int print_x(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	unsigned long int num;
	unsigned int retrn = 0;
	char *lead = "0x";

	if (len == LONG)
		num = va_arg(args, unsigned long int);
	else
		num = va_arg(args, unsigned int);
	if (len == SHORT)
		num = (unsigned short)num;
	if (HASH == 1 && num != 0)
		retrn += _memcpy(output, lead, 2);
	if (!(num == 0 && prec == 0))
		retrn += convert_ubase(output, num, "0123456789abcdef", flags, wid, prec);
	retrn += neg_width_printer(output, retrn, flags, wid);
	return (retrn);
}

/**
 * print_X - Converts an unsigned int argument to hex using ABCDEF
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @wid: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */

unsigned int print_X(va_list args, buffer_t *output, unsigned char flags,
		int wid, int prec, unsigned char len)
{
	unsigned long int num;
	unsigned int retrn = 0;
	char *lead = "0X";

	if (len == LONG)
		num = va_arg(args, unsigned long);
	else
		num = va_arg(args, unsigned int);
	if (len == SHORT)
		num = (unsigned short)num;
	if (HASH_F == 1 && num != 0)
		retrn += _memcpy(output, lead, 2);
	if (!(num == 0 && prec == 0))
		retrn += convert_ubase(output, num, "0123456789ABCDEF", flags, wid, prec);
	retrn += neg_width_printer(output, retrn, flags, wid);
	return (retrn);
}
