/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 10:15:08 by tde-nico          #+#    #+#             */
/*   Updated: 2022/01/19 10:15:17 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	display_number(unsigned long nbr, char *base, int base_n)
{
	if (nbr > 0)
	{
		display_number(nbr / base_n, base, base_n);
		write(1, base + nbr % base_n, 1);
	}
}

static void	count_number(int *chars, unsigned long nbr, char *base, int base_n)
{
	if (nbr > 0)
	{
		count_number(chars, nbr / base_n, base, base_n);
		(*chars)++;
	}
}

void	ft_putunbr_base(unsigned long nbr, char *base)
{
	if (nbr == 0)
		write(1, base, 1);
	display_number(nbr, base, ft_strlen(base));
}

int	ft_countunbr_base(unsigned long nbr, char *base)
{
	int	n;

	if (nbr == 0)
		return (1);
	n = 0;
	count_number(&n, nbr, base, ft_strlen(base));
	return (n);
}
