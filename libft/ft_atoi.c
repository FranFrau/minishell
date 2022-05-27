/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 12:19:23 by tde-nico          #+#    #+#             */
/*   Updated: 2022/01/20 08:47:21 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int					sign;
	int					i;
	unsigned long long	n;

	i = 0;
	sign = 1;
	n = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign *= -1;
	while (str[i] >= 48 && str[i] <= 57)
		n = (n * 10) + (str[i++] - 48);
	if (n >= 9223372036854775808ULL)
	{
		if (sign == 1)
			return (-1);
		else
			return (0);
	}
	return ((int)n * sign);
}
