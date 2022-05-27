/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 09:14:00 by tde-nico          #+#    #+#             */
/*   Updated: 2022/01/12 11:10:30 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*entry;

	entry = *lst;
	while (entry)
	{
		tmp = entry->next;
		if (del)
		{
			del(entry->content);
		}
		free(entry);
		entry = tmp;
	}
	*lst = NULL;
}
