/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:01:26 by jpajuelo          #+#    #+#             */
/*   Updated: 2023/03/30 10:01:26 by jpajuelo         ###   ########.fr       */
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*substr;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	i = 0;
	if (len > s_len)
		len = s_len;
	if (start >= s_len)
	{
		substr = (char *)malloc(1);
		if (substr == NULL)
			return (NULL);
		substr[0] = '\0';
		return (substr);
	}
	substr = (char *)malloc(len + 1);
	if (substr == NULL)
		return (NULL);
	while (i++ < start)
		s++;
	ft_strlcpy(substr, s, len + 1);
	return (substr);
}

static int	ft_count_words(const char *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		else
			i++;
	}
	return (count);
}

static char	**ft_fill_array(char **aux, char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		k;
	size_t	s_len;

	i = 0;
	k = 0;
	s_len = ft_strlen(s);
	while (s[i])
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		j = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		if (j >= s_len)
			aux[k++] = "\0";
		else
			aux[k++] = ft_substr(s, j, i - j);
	}
	return (aux);
}

char	**ft_split(char const *s, char c)
{
	char	**aux;
	int		nwords;

	if (!s)
		return (NULL);
	nwords = ft_count_words(s, c);
	aux = malloc((nwords + 1) * sizeof(char *));
	if (aux == NULL)
		return (NULL);
	aux = ft_fill_array(aux, s, c);
	aux[nwords] = NULL;
	return (aux);
}
