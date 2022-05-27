/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 10:14:29 by tde-nico          #+#    #+#             */
/*   Updated: 2022/01/26 11:10:35 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	init_flags(t_flags *flags)
{
	if (flags)
	{
		flags->zero = 0;
		flags->left = 0;
		flags->hash = 0;
		flags->sign = 0;
		flags->space = 0;
		flags->width = 0;
		flags->precision = -1;
		flags->length_h = 0;
		flags->length_hh = 0;
		flags->length_l = 0;
		flags->length_ll = 0;
		flags->type = '\0';
	}
}

void	process_flags(int *len, va_list args, t_flags *flags)
{
	if (flags->type == 'c')
		process_char(len, args, flags);
	else if (flags->type == 's')
		process_string(len, args, flags);
	else if (flags->type == 'p')
		process_pointer(len, args, flags);
	else if (flags->type == 'd' || flags->type == 'i')
		process_signed_decimal(len, args, flags);
	else if (flags->type == 'u')
		process_unsigned_decimal(len, args, flags);
	else if (flags->type == 'x')
		process_unsigned_hex_low(len, args, flags);
	else if (flags->type == 'X')
		process_unsigned_hex_up(len, args, flags);
	else if (flags->type == '%')
		process_percentage(len, flags);
}

static int	process_arg(const char *format, va_list args, int *len)
{
	t_flags		flags;
	const char	*original_format;

	original_format = format;
	init_flags(&flags);
	format += parse_flags(format, &flags);
	format += parse_width(format, args, &flags);
	format += parse_precision(format, args, &flags);
	format += parse_length(format, &flags);
	format += parse_type(format, &flags);
	process_flags(len, args, &flags);
	return (format - original_format);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;

	len = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format != '%')
		{
			ft_putchar_fd(*format++, 1);
			len++;
		}
		else
			format += process_arg(format, args, &len);
	}
	va_end(args);
	return (len);
}
