#ifndef MAIN_H
#define MAIN_H

#include <limits.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

/* Flag Modifier Macros */
#define PLUS 1
#define SPACE 2
#define HASH 4
#define ZERO 8
#define NEG 16
#define PLUS_F (flags & 1)
#define SPACE_F ((flags >> 1) & 1)
#define HASH_F ((flags >> 2) & 1)
#define ZERO_F ((flags >> 3) & 1)
#define NEG_F ((flags >> 4) & 1)

/* Length Modifier Macros */
#define SHORT 1
#define LONG 2

#define UNUSED(x) (void)(x)

/**
 * struct buffer_struct - A new type defining a buffer struct.
 * @buffer: A pointer to a character array.
 * @start: A pointer to the start of buffer.
 * @len: The length of the string stored in buffer.
 */

typedef struct buffer_struct
{
	char *buffer;
	char *start;
	unsigned int len;
} buffer_t;

/**
 * struct converter_struct - A new type defining a converter struct.
 * @specifier: A character representing a conversion specifier
 * @func: A pointer to a conversion function corresponding to specifier.
 */

typedef struct converter_struct
{
	unsigned char specifier;
	unsigned int (*func)(va_list, buffer_t *,
			unsigned char, int, int, unsigned char);
} converter_t;

/**
 * struct flag_struct - A new type defining a flags struct.
 * @flag: A character representing a flag.
 * @value: The integer value of the flag.
 */

typedef struct flag_struct
{
	unsigned char flag;
	unsigned char value;
} flag_t;

int _printf(const char *format, ...);

/* Conversion Specifier Functions */
unsigned int print_c(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int print_s(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int print_di(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int print_percent(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int print_b(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int print_u(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int print_o(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int print_x(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int print_X(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int print_S(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int print_p(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int print_r(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int print_R(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);

/* Handlers */
unsigned char flags_handler(const char *flags, char *index);
unsigned char length_handler(const char *modifier, char *index);
int width_handler(va_list args, const char *modifier, char *index);
int precision_handler(va_list args, const char *modifier, char *index);
unsigned int (*handle_specifiers(const char *specifier))(va_list, buffer_t *,
		unsigned char, int, int, unsigned char);

/* Modifiers */
unsigned int width_printer(buffer_t *output, unsigned int printed,
		unsigned char flags, int wid);
unsigned int string_width_printer(buffer_t *output, unsigned char flags,
		int wid, int prec, int size);
unsigned int neg_width_printer(buffer_t *output, unsigned int printed,
		unsigned char flags, int wid);

/* Helper Functions */
buffer_t *initialize_buffer(void);
void free_buffer(buffer_t *output);
unsigned int _memcpy(buffer_t *output, const char *src, unsigned int n);
unsigned int convert_sbase(buffer_t *output, long int num, char *base,
		unsigned char flags, int wid, int prec);
unsigned int convert_ubase(buffer_t *output, unsigned long int num, char *base,
		unsigned char flags, int wid, int prec);

#endif
