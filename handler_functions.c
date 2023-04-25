#include "main.h"

unsigned char flags_handler(const char *flag, char *index);
unsigned char length_handler(const char *modifier, char *index);
int width_handler(va_list args, const char *modifier, char *index);
int precision_handler(va_list args, const char *modifier, char *index);
unsigned int (*handle_specifiers(const char *specifier))(va_list, buffer_t *,
		unsigned char, int, int, unsigned char);

/**
 * flags_handler - Matches flags with corresponding values.
 * @flag: A pointer to a potential string of flags.
 * @index: An index counter for the original format string.
 *
 * Return: If flag characters are matched otherwise - 0.
 */

unsigned char flags_handler(const char *flag, char *index)
{
	int i, j;
	unsigned char retrn = 0;

	flag_t flags[] = {
		{'+', PLUS},
		{' ', SPACE},
		{'#', HASH},
		{'0', ZERO},
		{'-', NEG},
		{0, 0}};
	for (i = 0; flag[i]; i++)
	{
		for (j = 0; flags[j].flag != 0; j++)
		{
			if (flag[i] == flags[j].flag)
			{
				(*index)++;
				if (retrn == 0)
					retrn = flags[j].value;
				else
					retrn |= flags[j].value;
				break;
			}
		}
		if (flags[j].value == 0)
			break;
	}
	return (retrn);
}

/**
 * length_handler - Matches length modifiers with their corresponding value.
 * @modifier: A pointer to a potential length modifier.
 * @i: An index counter for the original format string.
 *
 * Return: If a lenth modifier is matched - its corresponding value.
 *         Otherwise - 0.
 */

unsigned char length_handler(const char *modifier, char *i)
{
	if (*modifier == 'h')
	{
		(*i)++;
		return (SHORT);
	}
	else if (*modifier == 'l')
	{
		(*i)++;
		return (LONG);
	}
	return (0);
}

/**
 * width_handler - Matches a width modifier with its corresponding value.
 * @args: A va_list of arguments.
 * @modifier: A pointer to a potential width modifier.
 * @i: An index counter for the original format string.
 *
 * Return: If a width modifier is matched - its value.
 *         Otherwise - 0.
 */

int width_handler(va_list args, const char *modifier, char *i)
{
	int val = 0;

	while ((*modifier >= '0' && *modifier <= '9') || (*modifier == '*'))
	{
		(*i)++;
		if (*modifier == '*')
		{
			val = va_arg(args, int);
			if (val <= 0)
				return (0);
			return (val);
		}
		val *= 10;
		val += (*modifier - '0');
		modifier++;
	}
	return (val);
}

/**
 * precision_handler - Matches a precision modifier with
 *                    its corresponding value.
 * @args: A va_list of arguments.
 * @modifier: A pointer to a potential precision modifier.
 * @i: An index counter for the original format string.
 *
 * Return: If a precision modifier is matched
 * If the precision modifier is empty, zero, or negative - 0 else -1.
 */

int precision_handler(va_list args, const char *modifier, char *i)
{
	int val = 0;

	if (*modifier != '.')
		return (-1);
	modifier++;
	(*i)++;
	if ((*modifier <= '0' || *modifier > '9') &&
			*modifier != '*')
	{
		if (*modifier == '0')
			(*i)++;
		return (0);
	}
	while ((*modifier >= '0' && *modifier <= '9') || (*modifier == '*'))
	{
		(*i)++;
		if (*modifier == '*')
		{
			val = va_arg(args, int);
			if (val <= 0)
				return (0);
			return (val);
		}
		val *= 10;
		val += (*modifier - '0');
		modifier++;
	}
	return (val);
}
/**
 * handle_specifiers - Matches a conversion specifier with
 *                     a corresponding conversion function.
 * @char: string
 * @int: integers
 *
 * Return: If a conversion function is matched - a pointer to the function.
 *         Otherwise - NULL.
 */
unsigned int (*handle_specifiers(const char *specifier))(va_list, buffer_t *,
		unsigned char, int, int, unsigned char)
{
	int i;
	converter_t converters[] = {
		{'c', print_c},
		{'s', print_s},
		{'d', print_di},
		{'i', print_di},
		{'%', print_percent},
		{'b', print_b},
		{'u', print_u},
		{'o', print_o},
		{'x', print_x},
		{'X', print_X},
		{'S', print_S},
		{'p', print_p},
		{'r', print_r},
		{'R', print_R},
		{0, NULL}
	};

	for (i = 0; converters[i].func; i++)
	{
		if (converters[i].specifier == *specifier)
			return (converters[i].func);
	}

	return (NULL);
}
