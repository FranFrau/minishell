/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_types_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 10:19:02 by tde-nico          #+#    #+#             */
/*   Updated: 2022/01/19 10:33:49 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	process_pointer(int *len, va_list args, t_flags *flags)
{
	unsigned long	n;
	int				s;
	int				d_n;

	n = va_arg(args, unsigned long);
	d_n = 2 + (n || flags->precision)
		* ft_countunbr_base(n, "0123456789abcdef");
	s = flags->width - d_n;
	if (flags->precision != -1 && flags->precision > d_n)
		s = flags->width - flags->precision;
	if (!flags->left)
	{
		add_filling((flags->zero && flags->precision == -1) * 16 + ' ', s, len);
		if (!flags->zero)
			ft_putstr_fd("0x", 1);
	}
	else if (!flags->zero)
		ft_putstr_fd("0x", 1);
	if (flags->precision != -1)
		add_filling('0', flags->precision - d_n + 2, len);
	if (n || flags->precision)
		ft_putunbr_base(n, "0123456789abcdef");
	(*len) += d_n;
	if (flags->left)
		add_filling(' ', s, len);
}

static void	process_unsigned_hex(int *len,
		unsigned int number, t_flags *flags, char *base)
{
	int				size;
	int				digs_number;

	digs_number = (number || flags->precision)
		* ft_countunbr_base(number, base);
	size = flags->width - digs_number;
	if (flags->precision != -1 && flags->precision > digs_number)
		size = flags->width - flags->precision;
	if (!flags->left)
		add_filling((flags->zero && flags->precision == -1) * 16 + ' ',
			size, len);
	if (flags->precision != -1)
		add_filling('0', flags->precision - digs_number, len);
	if (number || flags->precision)
	{
		ft_putunbr_base(number, base);
		(*len) += digs_number;
	}
	if (flags->left)
		add_filling(' ', size, len);
}

void	process_unsigned_hex_low(int *len, va_list args, t_flags *flags)
{
	unsigned int	number;

	number = va_arg(args, unsigned int);
	if (flags->hash && number)
	{
		ft_putstr_fd("0x", 1);
		(*len) += 2;
	}
	process_unsigned_hex(len, number, flags, "0123456789abcdef");
}

void	process_unsigned_hex_up(int *len, va_list args, t_flags *flags)
{
	unsigned int	number;

	number = va_arg(args, unsigned int);
	if (flags->hash && number)
	{
		ft_putstr_fd("0X", 1);
		(*len) += 2;
	}
	process_unsigned_hex(len, number, flags, "0123456789ABCDEF");
}

void	process_percentage(int *len, t_flags *flags)
{
	if (!flags->left)
		add_filling((flags->zero) * 16 + ' ', flags->width - 1, len);
	ft_putchar_fd('%', 1);
	(*len)++;
	if (flags->left)
		add_filling(' ', flags->width - 1, len);
}
