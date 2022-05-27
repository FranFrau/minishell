/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 08:13:03 by tde-nico          #+#    #+#             */
/*   Updated: 2022/01/21 09:07:33 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < (size_t)start || !len)
	{
		sub = malloc(sizeof(char));
		if (!sub)
			return (NULL);
		sub[0] = '\0';
		return (sub);
	}
	sub = malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	i = -1;
	while (++i < len && s[(size_t)start + i])
		sub[i] = s[(size_t)start + i];
	sub[i] = '\0';
	return (sub);
}
