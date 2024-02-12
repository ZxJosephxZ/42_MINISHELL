/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseph <joseph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:26:26 by joseph            #+#    #+#             */
/*   Updated: 2024/02/12 11:35:58 by joseph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

//Obtener variables de entorno
//Se ha establecido una pila FIFO en la estructura mini apuntando a env
//Tomando como pila env y los nodos a añadir como env_clone

int   get_env(t_mini *minishell, char **envp)
{
    int i;
    t_env *env;
    t_env *env_clone;
    
    i = 1;
    if (!(env = malloc(sizeof(t_env))))
        return (1);
    env->value = ft_strdup(envp[0]);
    env->next = NULL;
    minishell->env = env;
    while (envp && envp[0] && envp[i])
    {
        if (!(env_clone = malloc(sizeof(t_env))))
            return(1);
        env_clone->value = ft_strdup(envp[i]);
        env_clone->next = NULL;
        env->next = env_clone;
        env = env_clone;
        i++;
    }
    return (0);
    
};