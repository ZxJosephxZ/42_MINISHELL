/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:27:23 by jpajuelo          #+#    #+#             */
/*   Updated: 2023/04/02 10:04:10 by jpajuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int a)
{
	unsigned char	c_unsigned;

	c_unsigned = (unsigned char)a;
	if (c_unsigned == '\0')
		return ((char *)&str[ft_strlen(str)]);
	while (*str != '\0')
	{
		if (*str == c_unsigned)
			return ((char *)str);
		str++;
	}
	return (NULL);
}
