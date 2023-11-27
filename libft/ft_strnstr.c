/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:28:35 by jpajuelo          #+#    #+#             */
/*   Updated: 2023/04/02 10:52:47 by jpajuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *litle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (big[i] && i < len)
	{
		if (big[i] == litle[0])
		{
			while (litle[j] && i + j < len)
			{
				if (litle[j] != big[i + j])
				{
					break ;
				}
				j++;
			}
			if (!litle[j])
				return ((char *)big + i);
		}
		i++;
	}
	if (litle[0] == 0)
		return ((char *)big);
	return (NULL);
}
