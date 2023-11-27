/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:28:26 by jpajuelo          #+#    #+#             */
/*   Updated: 2023/04/03 10:40:15 by jpajuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t				i;
	const unsigned char	*c1;
	const unsigned char	*c2;

	c1 = (const unsigned char *)str1;
	c2 = (const unsigned char *)str2;
	if (n == 0)
	{
		return (0);
	}
	i = 0;
	while (c1[i] && c2[i] && c1[i] == c2[i] && i < (n - 1))
	{
		i++;
	}
	return (c1[i] - c2[i]);
}
