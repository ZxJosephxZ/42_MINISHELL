/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 09:47:03 by jpajuelo          #+#    #+#             */
/*   Updated: 2023/04/02 09:47:03 by jpajuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content)
{
	t_list	*newl;

	newl = (t_list *)malloc(1 * sizeof(t_list));
	if (newl == NULL)
		return (NULL);
	if (content == NULL)
		newl->content = NULL;
	else
		newl->content = (void *)content;
	newl->next = NULL;
	return (newl);
}
