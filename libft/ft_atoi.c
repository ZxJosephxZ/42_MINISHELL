/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:25:22 by jpajuelo          #+#    #+#             */
/*   Updated: 2023/04/02 10:02:15 by jpajuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//convertir una cadena de numero a entero.
int	ft_atoi(const char *str)
{
	int	signo;
	int	res;

	signo = 1;
	res = 0;
	while (*str == ' ' || *str == '\f' || *str == '\t' || *str == '\v'
		|| *str == '\n' || *str == '\r')
	{
		str++;
	}
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
		{
			signo = -1;
		}
		str++;
	}
	while ('0' <= *str && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res * signo);
}
