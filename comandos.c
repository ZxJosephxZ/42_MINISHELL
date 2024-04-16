/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comandos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:33:44 by jpajuelo          #+#    #+#             */
/*   Updated: 2024/04/16 11:41:01 by jpajuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	ft_putendl(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i] != '\0')
	{
		write(1, &s[i], 1);
		i++;
	}
	write(1, "\n", 1);
}

//Numero de argumentos 

static	int		nb_args(char **args)
{
	int		size;

	size = 0;
	while (args[size])
		size++;
	return (size);
}

//Establece el echo con flags

int				ft_echo(char **args)
{
	int		i;
	int		n_option;

	i = 1;
	n_option = 0;
	if (nb_args(args) > 1)
	{
		while (args[i] && ft_strcmp(args[i], "-n") == 0)
		{
			n_option = 1;
			i++;
		}
		while (args[i])
		{
			ft_putstr_fd(args[i], 1);
			if (args[i + 1] && args[i][0] != '\0')
				write(1, " ", 1);
			i++;
		}
	}
	if (n_option == 0)
		write(1, "\n", 1);
	return (SUCCESS);
}

//Obtener el path actual getcwd(current working directory)

int		ft_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
	{
		ft_putendl_fd(cwd, 1);
		return (SUCCESS);
	}
	else
		return (ERROR);
}

int		ft_env(t_env *env)
{
	while (env && env->next != NULL)
	{
		if (ft_strchr(env->value, '='))
			ft_putendl(env->value);
		env = env->next;
	}
	if (env)
	{
		ft_putendl(env->value);
	}
	return (SUCCESS);
}

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i] != '\0')
	{
		write(1, &s[i], 1);
		i++;
	}
}

void	show_export_env(char *str)
{
	int i;
	int lock;
	
	i = 0;
	lock = 0;
	while (str[i])
	{
		write(1,&str[i],1);
		if (str[i] == '=' && lock == 0)
		{
			write(1,"\"",1);
			lock++;
		}
		i++;
	}
	if (lock != 0)
		write(1,"\"",1);
	write(1,"\n",1);
}

void	ft_print_env_flag(t_env *env)
{
	while (env->next)
	{
		ft_putstr("declare -x ");
		show_export_env(env->value);
		env = env->next;
	}
}

int	valid_argument_env(const char *env)
{
	int	i;

	i = 0;
	if (ft_isdigit(env[i] == 1))
		return (0);
	while (env[i] && env[i] != '=')
	{
		if (ft_isalnum(env[i]) == 0)
		{
			return (-1);
		}
		i++;
	}
	/**if (env[i] != '=')
	{
		return (2);
	}**/
	return (1);
}

int	ft_print_type_error(int type, const char *expo_name)
{
	int i;
	
	if (type == -1)
	{
		ft_putstr_fd("export: not valid in this context: ", STDERR);
	}
	else if (type == 0 || type == -3)
	{
		ft_putstr_fd("export: not valid identifier: ", STDERR);
	}
	i = 0;
	while (expo_name[i] && (expo_name[i] != '=' || type == -3))
	{
		write(STDERR, &expo_name[i], 1);
		i++;
	}
	write (STDERR, "\n", 1);
	return (ERROR);
}

int	in_env(t_env *env, char *arg)
{
	char arg_name[4096];
	char env_name[4096];

	get_env_name(arg_name, arg);
	while (env && env->next)
	{
		get_env_name(env_name, env->value);
		if (ft_strcmp(env_name, arg_name) == 0)
		{
			ft_memdel(env->value);
			env->value = ft_strdup(arg);
			return (1);
		}
		env = env->next;
	}
	return (SUCCESS);
}

int	add_env(const char *arg, t_env *env)
{
	t_env *new;
	t_env *tmp;

	if (env && !env->value)
	{
		env->value = ft_strdup(arg);
	}
	if (!(new = malloc(sizeof(t_env))))
	{
		return (-1);
	}
	new->value = ft_strdup(arg);
	while (env && env->next && env->next->next)
		env = env->next;
	tmp = env->next;
	env->next = new;
	new->next = tmp;
	return (SUCCESS);
}

void replace_char(char *str, char find, char replace) {
    while (*str != '\0') {
        if (*str == find) {
            *str = replace;
        }
        str++;
    }
}

int	ft_directoryexport(char *path, t_env *env)
{
	DIR *dir;
    struct dirent *entry;
    char **files;
    int count = 0;
	int i = 0;
	(void)path;
    // Abrir el directorio actual
	if (ft_strcmp(path,"*"))
	{
		replace_char(path,'*','.');
		dir = opendir(path);
	}
    else
	{
		replace_char(path,'*','.');
		dir = opendir(path);
	}
    if (dir == NULL) {
        perror("Error al abrir el directorio");
        exit(EXIT_FAILURE);
    }

    // Contar la cantidad de archivos y carpetas en el directorio
    while ((entry = readdir(dir)) != NULL) {
        count++;
    }

    // Reservar memoria para el array de nombres de archivos
    files = (char **)malloc(count * sizeof(char *));
    if (files == NULL) {
        perror("Error al reservar memoria");
        closedir(dir);
        exit(EXIT_FAILURE);
    }

    // Reiniciar el puntero del directorio
    dir = opendir(path);

    // Almacenar los nombres de archivos en el array
    count = 0;
    while ((entry = readdir(dir)) != NULL) {
        files[count] = entry->d_name;
        count++;
    }
	
	while (i < count)
	{
		printf("%s",files[i]);
		ft_export2(files[i], env);
		i++;
	}
    // Liberar memoria y cerrar el directorio
    closedir(dir);
    free(files);

    return 0;
}

int		ft_export2(char *args, t_env *env)
{
	int	new_env;
	int	error_ret;

	new_env = 0;
	if (!args)
	{
		ft_print_env_flag(env);
		return (SUCCESS);
	}
	else
	{
		error_ret = valid_argument_env(args);
		if (ft_strcmp(args,"=")== 0)
			error_ret = -3;
		if (error_ret <= 0)
			return (ft_print_type_error(error_ret,args));
		if (error_ret == 2)
			new_env = 1;
		else
			new_env = in_env(env, args);
		if (new_env == 0)
		{
			if (error_ret == 1)
				add_env(args, env);
		}
	}
	return (SUCCESS);
}

int		ft_export(char **args, t_env *env)
{
	int	new_env;
	int	error_ret;

	new_env = 0;
	if (!args[1])
	{
		ft_print_env_flag(env);
		return (SUCCESS);
	}
	else
	{
		if (ft_strcmp(args[1],"*") == 0 || ((args[1][0] != '/' && args[1][ft_strlen(args[1]) - 1] != '/')
			&& ft_strchr(args[1], '/')))
			return (ft_directoryexport(args[1], env));
		error_ret = valid_argument_env(args[1]);
		if (args[1][0] == '=')
			error_ret = -3;
		if (error_ret <= 0)
			return (ft_print_type_error(error_ret,args[1]));
		if (error_ret == 2)
			new_env = 1;
		else
			new_env = in_env(env, args[1]);
		if (new_env == 0)
		{
			if (error_ret == 1)
				add_env(args[1], env);
		}
	}
	return (SUCCESS);
}

size_t	env_size(char *env)
{
	size_t		i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

void		free_node(t_mini *mini, t_env *env)
{
	if (mini->env == env && env->next == NULL)
	{
		ft_memdel(mini->env->value);
		mini->env->value = NULL;
		mini->env->next = NULL;
		return ;
	}
	ft_memdel(env->value);
	ft_memdel(env);
}

int	ft_unset(char **args, t_mini *mini)
{
	t_env *env;
	t_env *tmp;
	
	env = mini->env;
	if (!(args[1]))
	{
		return (SUCCESS);
	}
	if (ft_strncmp(args[1], env->value, env_size(env->value)) == 0)
	{
		if (env->next)
		{
			mini->env = env->next;
		}
		free_node(mini, env);
		return (SUCCESS);
	}
	while (env && env->next)
	{
		if (ft_strncmp(args[1], env->next->value, env_size(env->next->value)) == 0)
		{
			tmp = env->next->next;
			free_node(mini, env->next);
			env->next = tmp;
			return (SUCCESS);
		}
		env = env->next;
	}
	return (SUCCESS);
}