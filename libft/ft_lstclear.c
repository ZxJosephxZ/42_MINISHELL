/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 09:45:37 by jpajuelo          #+#    #+#             */
/*   Updated: 2023/04/02 09:45:37 by jpajuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	int		i;
	int		size;
	t_list	*aux;

	i = 0;
	size = ft_lstsize(*lst);
	while (i < size && *lst)
	{
		aux = (*lst)->next;
		del((*lst)->content);
		if (*lst != NULL)
		{
			free(*lst);
		}
		*lst = aux;
	}
	lst = NULL;
}
