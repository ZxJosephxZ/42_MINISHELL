/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:12:16 by jpajuelo          #+#    #+#             */
/*   Updated: 2023/03/30 10:12:16 by jpajuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_contador_digitos(int n)
{
	int	count;

	count = 0;
	while (n != 0)
	{
		n /= 10;
		if (n != 0)
		{
			count++;
		}
	}
	return (++count);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			i;
	long int	nb;
	int			signo;

	i = ft_contador_digitos(n);
	signo = n < 0;
	nb = n;
	if (signo)
		nb = -(long)n;
	i += signo;
	str = ft_calloc(i + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	str[i--] = 0;
	while (i >= signo)
	{
		str[i] = nb % 10 + '0';
		nb /= 10;
		i--;
	}
	if (signo)
		str[0] = '-';
	return (str);
}
