/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 10:41:18 by jpajuelo          #+#    #+#             */
/*   Updated: 2023/04/01 10:41:18 by jpajuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*source;
	char	*dest;

	source = (char *)src;
	dest = (char *)dst;
	if (!dst && !src)
		return (dst);
	while (n--)
		*dest++ = *source++;
	return (dst);
}
