/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:27:53 by jpajuelo          #+#    #+#             */
/*   Updated: 2023/04/02 11:27:36 by jpajuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *str1, const char *str2, size_t n)
{
	unsigned int	i;
	int				counter;

	counter = (unsigned int)ft_strlen(str2);
	if (!n)
	{
		return (counter);
	}
	i = 0;
	while (str2[i] && i < (n - 1))
	{
		str1[i] = str2[i];
		i++;
	}
	str1[i] = '\0';
	return (counter);
}
