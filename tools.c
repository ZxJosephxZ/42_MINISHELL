/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:47:50 by jpajuelo          #+#    #+#             */
/*   Updated: 2024/02/27 13:24:37 by jpajuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

//Comprobacion y retorno de el valor de la variable.

char	*get_var_value(const char *arg, int pos, t_env *env, int ret)
{
	char	var_name[4096];
	char	*var_value;
	int		i;

	i = 0;
	if (arg[pos] == '?')
	{
		var_value = ft_itoa(ret);
		return (var_value);
	}
	if (ft_isdigit(arg[pos]))
		return (NULL);
	while (arg[pos] && is_env_char(arg[pos]) == 1 && i < 4096)
	{
		var_name[i] = arg[pos];
		pos++;
		i++;
	}
	var_name[i] = '\0';
	var_value = get_env_value(var_name, env);
	return (var_value);
}

//Si es un caso de variable de entorno

int		is_env_char(int c)
{
	if (ft_isalnum(c) == 1 || c == '_')
		return (1);
	return (0);
}

//En el caso $? imprimir 0 o 1

int		ret_size(int ret)
{
	char	*tmp;
	int		ret_len;

	tmp = ft_itoa(ret);
	ret_len = ft_strlen(tmp);
	ft_memdel(tmp);
	return (ret_len);
}

//obtencion de la longitud real de la variable

int		get_var_len(const char *arg, int pos, t_env *env, int ret)
{
	char	var_name[4096];
	char	*var_value;
	int		i;

	i = 0;
	if (arg[pos] == '?')
		return (ret_size(ret));
	if (ft_isdigit(arg[pos]))
		return (0);
	while (arg[pos] && is_env_char(arg[pos]) == 1 && i < 4096)
	{
		var_name[i] = arg[pos];
		pos++;
		i++;
	}
	var_name[i] = '\0';
	var_value = get_env_value(var_name, env);
	i = ft_strlen(var_value);
	ft_memdel(var_value);
	return (i);
}

//Contabilizar la longitud del argumento

int		arg_alloc_len(const char *arg, t_env *env, int ret)
{
	int		i;
	int		size;

	i = -1;
	size = 0;
	while (arg[++i])
	{
		//36 == $
		if (arg[i] == EXPANSION)
		{
			i++;
			if ((arg[i] == '\0' || ft_isalnum(arg[i]) == 0) && arg[i] != '?')
				size++;
			else
				size += get_var_len(arg, i, env, ret);
			if (ft_isdigit(arg[i]) == 0)
			{
				while (arg[i + 1] && is_env_char(arg[i]))
					i++;
			}
			else
				size--;
		}
		size++;
	}
	return (size);
}

//Copia la variable y devuelve el numero de iteraciones

static int		varlcpy(char *new_arg, const char *env_value, int pos)
{
	int		i;

	i = 0;
	while (env_value[i])
		new_arg[pos++] = env_value[i++];
	return (i);
}

void		insert_var(t_expansions *ex, char *arg, t_env *env, int ret)
{
	char	*env_value;

	env_value = get_var_value(arg, ex->j, env, ret);
    if (env_value)
    {
        ex->i += varlcpy(ex->new_arg, env_value, ex->i);
    }
	ft_memdel(env_value);
	if (arg[ex->j] == '?')
	{
		ex->j++;
	}
	if (ft_isdigit(arg[ex->j]) == 0 && arg[ex->j - 1] != '?')
	{
		while (is_env_char(arg[ex->j]) == 1)
			ex->j++;
	}
	else
	{
		if (arg[ex->j - 1] != '?')
			ex->j++;
	}
}
