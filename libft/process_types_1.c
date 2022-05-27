/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_types_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 10:18:47 by tde-nico          #+#    #+#             */
/*   Updated: 2022/01/19 10:34:31 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	process_char(int *len, va_list args, t_flags *flags)
{
	if (flags->left)
		ft_putchar_fd((unsigned char)va_arg(args, int), 1);
	add_filling(' ', flags->width - 1, len);
	if (!flags->left)
		ft_putchar_fd((unsigned char)va_arg(args, int), 1);
	(*len)++;
}

void	process_string(int *len, va_list args, t_flags *flags)
{
	int		displayed;
	char	*string;
	int		size;

	displayed = 0;
	string = va_arg(args, char *);
	if (!string)
		string = "(null)";
	size = flags->width - ft_strlen(string);
	if (ft_strlen(string) > (size_t)flags->precision)
		size = flags->width - flags->precision;
	if (!flags->left)
		add_filling(flags->zero * 16 + ' ', size, len);
	while (*string && (displayed < flags->precision || flags->precision == -1))
	{
		ft_putchar_fd(*string++, 1);
		(*len)++;
		displayed++;
	}
	if (flags->left)
		add_filling(' ', size, len);
}

void	process_unsigned_decimal(int *len, va_list args, t_flags *flags)
{
	unsigned int	number;
	int				s;
	int				digs_number;

	number = va_arg(args, unsigned int);
	digs_number = (number || flags->precision) * count_digits_unsig(number);
	s = flags->width - digs_number;
	if (flags->precision != -1 && flags->precision > digs_number)
		s = flags->width - flags->precision;
	if (flags->sign && number)
	{
		ft_putchar_fd('+', 1);
		(*len)++;
	}
	if (!flags->left)
		add_filling((flags->zero && flags->precision == -1) * 16 + ' ', s, len);
	if (flags->precision != -1)
		add_filling('0', flags->precision - digs_number, len);
	if (number || flags->precision)
	{
		ft_putunbr_base(number, "0123456789");
		(*len) += digs_number;
	}
	if (flags->left)
		add_filling(' ', s, len);
}

void	process_signed_decimal(int *len, va_list args, t_flags *flags)
{
	int	number;
	int	s;

	number = va_arg(args, int);
	s = fill_size_sing_int(flags, number);
	if (flags->zero && flags->precision == -1 && number < 0)
		ft_putchar_fd('-', 1);
	if (flags->sign && number >= 0)
	{
		ft_putchar_fd('+', 1);
		(*len)++;
	}
	if (s < 0 && number >= 0)
		add_filling(' ', flags->space, len);
	if (!flags->left)
		add_filling((flags->zero && flags->precision == -1) * 16 + ' ', s, len);
	if (!(flags->zero && flags->precision == -1) && number < 0)
		ft_putchar_fd('-', 1);
	if (flags->precision != -1)
		add_filling('0', flags->precision - count_digits_sig(number, 0), len);
	process_signed_decimal_2(len, number, flags, s);
}

void	process_signed_decimal_2(int *len, int number, t_flags *flags, int s)
{
	int	digs_nbr;
	int	min;

	digs_nbr = (number || flags->precision) * count_digits_sig(number, 1);
	min = 0;
	if (number < 0)
	{
		min = !(flags->precision - digs_nbr);
		number = -number;
	}
	if (number || flags->precision)
	{
		ft_putunbr_base((unsigned int)number, "0123456789");
		(*len) += digs_nbr;
	}
	if (flags->left)
		add_filling(' ', s - min, len);
}
