/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 08:24:14 by tde-nico          #+#    #+#             */
/*   Updated: 2022/01/17 10:59:33 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char	*map;
	int		i;

	if (!s || !f)
		return (NULL);
	map = (char *) malloc(sizeof(*map) * (ft_strlen(s) + 1));
	if (!map)
		return (NULL);
	i = -1;
	while (s[++i])
		map[i] = f(i, s[i]);
	map[i] = '\0';
	return (map);
}
