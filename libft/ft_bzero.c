/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:25:32 by jpajuelo          #+#    #+#             */
/*   Updated: 2023/04/01 10:27:13 by jpajuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_bzero(void *str, size_t z)
{
	unsigned char	*str1;

	str1 = (unsigned char *)str;
	while (z-- > 0)
	{
		*(str1++) = '\0';
	}
	return (str);
}
