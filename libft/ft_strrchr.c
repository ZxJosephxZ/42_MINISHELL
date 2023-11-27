/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:28:42 by jpajuelo          #+#    #+#             */
/*   Updated: 2023/04/02 10:54:43 by jpajuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int				last;
	unsigned char	c_unsigned;

	c_unsigned = (unsigned char)c;
	if (c_unsigned == '\0')
		return ((char *)&str[ft_strlen(str)]);
	last = ft_strlen(str) - 1;
	if (last < 0)
		return (NULL);
	while (last >= 0)
	{
		if (str[last] == c_unsigned)
			return ((char *)&str[last]);
		last--;
	}
	return (NULL);
}
