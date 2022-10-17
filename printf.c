#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include "main.h"

/**
 * buffer_const_char - function that puts constant format chars into buffer
 *
 * @format: format string
 *
 * @buffer: output buffer
 *
 * @len: length of current buffer contents
 *
 * Return: number of chars put into buffer
 */
int buffer_const_char(char **format, char *buffer, unsigned int *len)
{
	int printtotal = 0;

	while (**format != 0 && **format != '%')
	{
		buffer[(*len)++] = **format;
		(*format)++;
		if (*len == 1024)
		{
			write(1, buffer, 1024);
			*len = 0;
			printtotal += 1024;
		}
	}
	return (printtotal);
}

/**
 * stringize_arg - Sends va_arg to appropriate function,
 * or returns a string for % or %c
 *
 * @list: va_list to pop from
 * @spec: struct of specifier info
 * @freeflag: set if we need to free a malloc
 *
 * Return: string to add to buffer
 */
char *stringize_arg(va_list list, specifier spec, unsigned int *freeflag)
{
	static char tmpstr[2] = {0, 0};
	char *tmp;

	switch (spec.specifier)
	{
	case 'n':
		tmpstr[0] = 0;
		return (tmpstr);
	case '%':
		tmpstr[0] = '%';
		return (tmpstr);
	case 'c':
		tmpstr[0] = (char) va_arg(list, int);
		*freeflag = 1;
		return (prep_string(tmpstr, spec));
	case 's':
		*freeflag = 1;
		tmp = va_arg(list, char*);
		return (prep_string(tmp, spec));
	case 'd':
	case 'i':
		*freeflag = 1;
		if (spec.length == 1)
			return (prep_numeric(litos(list), spec));
		if (spec.length == -1)
			return (prep_numeric(hitos(list), spec));
		if (spec.length < -1)
			return (prep_numeric(hhitos(list), spec));
		return (prep_numeric(itos(list), spec));
	case 'b':
		*freeflag = 1;
		if (spec.length == 1)
			return (prep_numeric(luitob(list), spec));
		if (spec.length == -1)
			return (prep_numeric(huitob(list), spec));
		if (spec.length < -1)
			return (prep_numeric(hhuitob(list), spec));
		return (prep_numeric(uitob(list), spec));
	case 'u':
		*freeflag = 1;
		if (spec.length == 1)
			return (prep_numeric(lutos(list), spec));
		if (spec.length == -1)
			return (prep_numeric(hutos(list), spec));
		if (spec.length < -1)
			return (prep_numeric(hhutos(list), spec));
		return (prep_numeric(utos(list), spec));

	case 'o':
		*freeflag = 1;
		if (spec.length == 1)
			return (prep_numeric(litoo(list), spec));
		if (spec.length == -1)
			return (prep_numeric(hitoo(list), spec));
		if (spec.length < -1)
			return (prep_numeric(hhitoo(list), spec));
		return (prep_numeric(itoo(list), spec));
	case 'x':
		*freeflag = 1;
		if (spec.length == 1)
			return (prep_numeric(litox(list), spec));
		if (spec.length == -1)
			return (prep_numeric(hitox(list), spec));
		if (spec.length < -1)
			return (prep_numeric(hhitox(list), spec));
		return (prep_numeric(itox(list), spec));
	case 'X':
		*freeflag = 1;
		if (spec.length == 1)
			return (prep_numeric(litoX(list), spec));
		if (spec.length == -1)
			return (prep_numeric(hitoX(list), spec));
		if (spec.length < -1)
			return (prep_numeric(hhitoX(list), spec));
		return (prep_numeric(itoX(list), spec));
	case 'r':
		*freeflag = 1;
		tmp = rev(va_arg(list, char*));
		if (tmp != NULL)
			return (prep_string(tmp, spec));
		return (NULL);
	case 'R':
		*freeflag = 1;
		tmp = rot(va_arg(list, char*));
		if (tmp != NULL)
			return (prep_string(tmp, spec));
		return (NULL);
	case 'S':
		*freeflag = 1;
		tmp = print_hidden(va_arg(list, char*));
		if (tmp != NULL)
			return (prep_string(tmp, spec));
		return (NULL);
	case 'p':
		*freeflag = 1;
		return (prep_numeric(litox(list), spec));
	}
	return (NULL);
}
