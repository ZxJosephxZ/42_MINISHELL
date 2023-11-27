/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:27:37 by jpajuelo          #+#    #+#             */
/*   Updated: 2023/04/02 12:22:15 by jpajuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*d;
	int		len;
	int		i;

	len = ft_strlen(s) + 1;
	d = ft_calloc(len, sizeof(char));
	i = 0;
	if (d != NULL)
	{
		while (i < len - 1)
		{
			d[i] = s[i];
			i++;
		}
		d[i] = 0;
	}
	return (d);
}
