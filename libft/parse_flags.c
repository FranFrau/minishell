/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 10:15:30 by tde-nico          #+#    #+#             */
/*   Updated: 2022/01/19 10:16:50 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	parse_flags(const char *format, t_flags *flags)
{
	int	chars_proc;

	format++;
	chars_proc = 1;
	while (ft_strchr("-0# +", *format))
	{
		if (*format == '-')
			flags->left = 1;
		else if (*format == '0')
			flags->zero = 1;
		else if (*format == '#')
			flags->hash = 1;
		else if (*format == ' ')
			flags->space = 1;
		else if (*format == '+')
			flags->sign = 1;
		chars_proc++;
		format++;
	}
	return (chars_proc);
}

int	parse_width(const char *format, va_list args, t_flags *flags)
{
	if (!*format)
		return (0);
	else if (*format == '*')
	{
		flags->width = va_arg(args, int);
		if (flags->width < 0)
		{
			flags->width *= -1;
			flags->left = 1;
		}
		return (1);
	}
	flags->width = ft_atoi(format);
	return (count_numbers(format));
}

int	parse_precision(const char *format, va_list args, t_flags *flags)
{
	if (!*format)
		return (0);
	else if (!(*format++ == '.'))
		return (0);
	else if (*format == '*')
	{
		flags->precision = va_arg(args, int);
		if (flags->precision < 0)
			flags->precision = -1;
		return (2);
	}
	else if (!ft_isdigit(*format))
	{
		flags->precision = 0;
		return (1);
	}
	flags->precision = ft_atoi(format);
	return (count_numbers(format) + 1);
}

int	parse_length(const char *format, t_flags *flags)
{
	if (!*format)
		return (0);
	else if (*format == 'h' && format[1] != 'h')
	{
		flags->length_h = 1;
		return (1);
	}
	else if (*format == 'h' && format[1] == 'h')
	{
		flags->length_hh = 1;
		return (2);
	}
	else if (*format == 'l' && format[1] != 'l')
	{
		flags->length_l = 1;
		return (1);
	}
	else if (*format == 'l' && format[1] == 'l')
	{
		flags->length_ll = 1;
		return (2);
	}
	return (0);
}

int	parse_type(const char *format, t_flags *flags)
{
	if (!*format)
		return (0);
	else if (ft_strchr("cspdiuxX%", *format))
	{
		flags->type = *format;
		return (1);
	}
	return (0);
}
