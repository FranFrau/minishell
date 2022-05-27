/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 08:14:48 by tde-nico          #+#    #+#             */
/*   Updated: 2022/01/13 08:23:50 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*format_itoa(int mem, char *str, int size)
{
	while (mem > 9 || mem < -9)
	{
		if (mem < 0)
			str[size--] = -(mem % 10) + '0';
		else
			str[size--] = mem % 10 + '0';
		mem = mem / 10;
	}
	str[0] = (mem + '0');
	if (mem < 0)
	{
		str[0] = '-';
		str[1] = (-mem + '0');
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	size;
	int		mem;

	mem = n;
	size = 2;
	if (n < 0)
		size = 3;
	while ((n > 9 || n < -9) && size++)
		n /= 10;
	str = (char *) malloc((size--) * sizeof(*str));
	if (!str)
		return (NULL);
	str[size--] = '\0';
	return (format_itoa(mem, str, size));
}
