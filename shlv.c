/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:59:12 by joseph            #+#    #+#             */
/*   Updated: 2024/02/13 12:44:52 by jpajuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

static char *get_env_name(char *dest, const char *src)
{
    int i;

    i = 0;
    while (src[i] && src[i] != '=' && ft_strlen(src) < 4096)
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

//Se salta caracteres especiales

void    ft_jump_space(const char *str, int *i)
{
    while ((str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\n') || (str[*i] == '\r' || str[*i] == '\v' || str[*i] == '\f'))
        (*i)++;
}

//Segun la consola el numero de procesos contados va de 0 a 9

static int invalid_lv(const char *str)
{
    int i;
    
    i = 0;
    while (str[i])
    {
        if (!(str[i] >= '0' && str[i] <= '9'))
            return (1);
        i++;
    }
    return (0);
}

//obtener la longitud de las variables de entorno

static int get_env_len(char *value)
{
    int i;
    int j;

    j = 0;
    i = 0;
    while (value[j] && value[j] != '=')
    {
        j++;
    }
    j += 1;
    while (value[j])
    {
        j++;
        i++;
    }
    return (j);
}

//Obtiene solo la parte del lv =

static int get_lv(const char *str)
{
    int i;
    int sign;
    int num;
    
    i = 0;
    sign = 1;
    num = 0;
    ft_jump_space(str, &i);
    if (invalid_lv(str))
        return (0);
    if (str[i] == '-')
        sign = -1;
    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str[i] >= '0' && str[i] <= '9')
        num = num * 10 + (str[i++] - '0');
    return (num * sign);
}

//La obtencion del parametro

static char *reference_value(char *value)
{
    int i;
    int j;
    int size_alloc;
    char *env_value;

    size_alloc = get_env_len(value) + 1;
    if (!(env_value = malloc(sizeof(char) * size_alloc)))
    {
        return NULL;
    }
    i = 0;
    while (value[i] && value[i] != '=')
    {
        i++;
    }
    i += 1;
    j = 0;
    while (value[i])
    {
        env_value[j++] = value[i++];
    }
    env_value[j] = '\0';
    return (env_value);
}

static char    *get_env_lv(char *reference, t_env *env)
{
    char    *env_value;
    char    matrix_value[4096];

    env_value = ft_strdup("");
    while (env && env->value)
    {
        get_env_name(matrix_value, env->value);
        if (ft_strcmp(reference, matrix_value) == 0)
        {
            ft_memdel(env_value);
            env_value = reference_value(env->value);
            return (env_value);
        }
        env = env->next;
    }
    return (env_value);
}

//Pues la comprobacion y aumento del shlvl

void    increment_shlv(t_env *env)
{
    int shell_lv;
    char env_matrix[4096];
    char *lv;
    char *value_shell;

    value_shell = get_env_lv("SHLVL", env);
    if (ft_strcmp(value_shell, "") == 0)
        return ;
    shell_lv = get_lv(value_shell) + 1;
    ft_memdel(value_shell);
    while (env && env->next)
    {
        get_env_name(env_matrix, env->value);
        if (ft_strcmp("SHLVL", env_matrix) == 0)
        {
            ft_memdel(env->value);
            lv = ft_itoa(shell_lv);
            env->value = ft_strjoin("SHLVL", lv);
            ft_memdel(lv);
            return ;
        }
        env = env->next;
    }
}