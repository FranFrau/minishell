/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 10:19:11 by tde-nico          #+#    #+#             */
/*   Updated: 2022/01/19 10:19:51 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	add_filling(char char_fill, int size, int *len)
{
	int	i;

	i = 0;
	while (i < size)
	{
		ft_putchar_fd(char_fill, 1);
		(*len)++;
		i++;
	}
}

int	count_numbers(const char *str)
{
	int	n;

	n = 0;
	while (ft_isdigit(str[n]))
		n++;
	return (n);
}

int	count_digits_unsig(unsigned int n)
{
	int	digits;

	if (n == 0)
		return (1);
	digits = 0;
	while (n > 0)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

int	count_digits_sig(int n, int include_sign)
{
	int		digits;
	long	ln;

	if (n == 0)
		return (1);
	digits = 0;
	ln = n;
	if (ln < 0)
	{
		if (include_sign)
			digits++;
		ln *= -1;
	}
	while (ln > 0)
	{
		ln /= 10;
		digits++;
	}
	return (digits);
}

int	fill_size_sing_int(t_flags *flags, int number)
{
	int	precision_correction;
	int	digits_sig;
	int	digits_unsig;

	digits_sig = (number || flags->precision) * count_digits_sig(number, 1);
	digits_unsig = count_digits_sig(number, 0);
	if (flags->precision != -1 && flags->precision > digits_sig)
		precision_correction = flags->precision - digits_unsig;
	else
		precision_correction = 0;
	return (flags->width - digits_sig - precision_correction);
}
