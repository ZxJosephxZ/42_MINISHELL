/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:26:58 by jpajuelo          #+#    #+#             */
/*   Updated: 2023/04/02 11:33:34 by jpajuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	size_t			i;
	unsigned char	*strx;
	unsigned char	*srcx;

	strx = (unsigned char *)str1;
	srcx = (unsigned char *)str2;
	i = 0;
	while (n > 0)
	{
		if (strx[i] == srcx[i])
		{
			i++;
		}
		else
		{
			return (strx[i] - srcx[i]);
		}
		n--;
	}
	return (0);
}
