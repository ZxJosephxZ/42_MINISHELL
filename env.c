/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:26:26 by joseph            #+#    #+#             */
/*   Updated: 2024/04/15 13:03:20 by jpajuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

//Obtener variables de entorno
//Se ha establecido una pila FIFO en la estructura mini apuntando a env
//Tomando como pila env y los nodos a añadir como env_clone

t_env *getminienv()
{
	t_env	*env;
	t_env	*env_clone;
	t_env	*env_clone1;
	t_env	*env_clone2;
	int i = 1;
	if (!(env = malloc(sizeof(t_env))))
		return (NULL);
	env->value = ft_strdup("SHLVL=1");
	env->next = NULL;
	env_clone1 = malloc(sizeof(t_env));
	env_clone2 = malloc(sizeof(t_env));
	env_clone1->value = ft_strdup("PWD=/Users/jpajuelo/projectocursus/Minishell");
	env_clone2->value = ft_strdup("PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/share/dotnet:/usr/local/munki:~/.dotnet/tools:/Library/Frameworks/Mono.framework/Versions/Current/Commands");
	env_clone2->next = NULL;
	env->next = env_clone1;
	env_clone1->next = env_clone2;
	//env->next->next = env_clone2;
	while (i != 2)
	{
		if (!(env_clone = malloc(sizeof(t_env))))
			return (NULL);
		env_clone->value = ft_strdup("_=/usr/bin/env");
		env_clone->next = NULL;
		env_clone2->next = env_clone;
		//env->next->next->next = env_clone;
		i++;
	}
	return (env);
}

int	get_env(t_mini *minishell, char **envp)
{
	t_env	*env;
	t_env	*env_clone;
	int		i;

	i = 1;
	if (!(env = malloc(sizeof(t_env))))
		return (1);
	env->value = ft_strdup(envp[0]);
	env->next = NULL;
	minishell->env = env;
	while (envp && envp[0] && envp[i])
	{
		if (!(env_clone = malloc(sizeof(t_env))))
			return (1);
		env_clone->value = ft_strdup(envp[i]);
		env_clone->next = NULL;
		env->next = env_clone;
		env = env_clone;
		i++;
	}
	return (0);
}

char		*get_env_name(char *dest, const char *src)
{
	int		i;

	i = 0;
	while (src[i] && src[i] != '=' && ft_strlen(src) < 4096)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int		env_value_len(const char *env)
{
	int		i;
	int		size_name;

	size_name = 0;
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	i += 1;
	while (env[i])
	{
		i++;
		size_name++;
	}
	return (size_name);
}

char	*env_value(char *env)
{
	int		i;
	int		j;
	int		size_alloc;
	char	*env_value;

	size_alloc = env_value_len(env) + 1;
	if (!(env_value = malloc(sizeof(char) * size_alloc)))
		return (NULL);
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	i += 1;
	j = 0;
	while (env[i])
		env_value[j++] = env[i++];
	env_value[j] = '\0';
	return (env_value);
}

char	*get_env_value(char *arg, t_env *env)
{
	char	env_name[4096];
	char	*env_val;

	env_val = ft_strdup("");
	while (env && env->value)
	{
		get_env_name(env_name, env->value);
		if (ft_strcmp(arg, env_name) == 0)
		{
			ft_memdel(env_val);
			env_val = env_value(env->value);
			return (env_val);
		}
		env = env->next;
	}
	return (env_val);
}