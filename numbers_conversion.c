#include "main.h"

unsigned int print_di(va_list args, buffer_t *output, unsigned char flags,
		int wid, int prec, unsigned char len);
unsigned int print_b(va_list args, buffer_t *output, unsigned char flags,
		int wid, int prec, unsigned char len);
unsigned int print_u(va_list args, buffer_t *output, unsigned char flags,
		int wid, int prec, unsigned char len);
unsigned int print_o(va_list args, buffer_t *output, unsigned char flags,
		int wid, int prec, unsigned char len);

/**
 * print_di - Converts an argument to a signed int.
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @wid: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int print_di(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	long int digit, copy;
	unsigned int retrn = 0, count = 0;
	char pad, space = ' ', neg = '-', plus = '+';

	if (len == LONG)
		digit = va_arg(args, long int);
	else
		digit = va_arg(args, int);
	if (len == SHORT)
		digit = (short)digit;

	if (SPACE_F == 1 && digit >= 0)
		retrn += _memcpy(output, &space, 1);

	if (prec <= 0 && NEG_F == 0) /* Handle width  */
	{
		if (digit == LONG_MIN)
			count += 19;
		else
		{
			for (copy = (digit < 0) ? -digit : digit; copy > 0; copy /= 10)
				count++;
		}
		count += (digit == 0) ? 1 : 0;
		count += (digit < 0) ? 1 : 0;
		count += (PLUS_F == 1 && digit >= 0) ? 1 : 0;
		count += (SPACE_F == 1 && digit >= 0) ? 1 : 0;

		if (ZERO_F == 1 && PLUS_F == 1 && digit >= 0)
			retrn += _memcpy(output, &plus, 1);
		if (ZERO_F == 1 && digit < 0)
			retrn += _memcpy(output, &neg, 1);

		pad = (ZERO_F == 1) ? '0' : ' ';
		for (wid -= count; wid > 0; wid--)
			retrn += _memcpy(output, &pad, 1);
	}
	if (ZERO_F == 0 && digit < 0)
		retrn += _memcpy(output, &neg, 1);
	if (ZERO_F == 0 && (PLUS_F == 1 && digit >= 0))
		retrn += _memcpy(output, &plus, 1);

	if (!(digit == 0 && prec == 0))
		retrn += convert_sbase(output, digit, "0123456789", flags, 0, prec);

	retrn += neg_width_printer(output, retrn, flags, wid);

	return (retrn);
}

/**
 * print_b - Converts an unsigned int argument to binary
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @wid: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int print_b(va_list args, buffer_t *output, unsigned char flags,
		int wid, int prec, unsigned char len)
{
	unsigned int num;

	num = va_arg(args, unsigned int);

	(void)len;

	return (convert_ubase(output, num, "01", flags, wid, prec));
}

/**
 * print_o - Converts an unsigned int to octal
 * @args: A va_list poinitng to the argument to be converted.
 * @flags: Flag modifiers.
 * @wid: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int print_o(va_list args, buffer_t *output, unsigned char flags,
		int wid, int prec, unsigned char len)
{
	unsigned long int num;
	unsigned int retrn = 0;
	char zero = '0';

	if (len == LONG)
		num = va_arg(args, unsigned long int);
	else
		num = va_arg(args, unsigned int);
	if (len == SHORT)
		num = (unsigned short)num;

	if (HASH_F == 1 && num != 0)
		retrn += _memcpy(output, &zero, 1);

	if (!(num == 0 && prec == 0))
		retrn += convert_ubase(output, num, "01234567", flags, wid, prec);

	retrn += neg_width_printer(output, retrn, flags, wid);

	return (retrn);
}

/**
 * print_u - Converts an unsigned int argument to decimal
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @wid: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int print_u(va_list args, buffer_t *output, unsigned char flags,
		int wid, int prec, unsigned char len)
{
	unsigned long int num;
	unsigned int retrn = 0;

	if (len == LONG)
		num = va_arg(args, unsigned long int);
	else
		num = va_arg(args, unsigned int);
	if (len == SHORT)
		num = (unsigned short)num;
	if (!(num == 0 && prec == 0))
		retrn += convert_ubase(output, num, "0123456789", flags, wid, prec);

	retrn += neg_width_printer(output, retrn, flags, wid);

	return (retrn);
}
