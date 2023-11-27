/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:27:08 by jpajuelo          #+#    #+#             */
/*   Updated: 2023/04/03 10:56:23 by jpajuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *str, const void *src, size_t n)
{
	size_t			i;
	char			*str1;
	char			*str2;

	str1 = (char *)str;
	str2 = (char *)src;
	if (str1 == NULL && str2 == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (src > str && i < n)
	{
		str1[i] = str2[i];
		i++;
	}
	while (src <= str && n > 0)
	{
		str1[n - 1] = str2[n - 1];
		n--;
	}
	return (str);
}
