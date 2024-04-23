/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:05:43 by jpajuelo          #+#    #+#             */
/*   Updated: 2024/04/23 12:33:27 by jpajuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

//si es un numero en string
size_t			size_env(t_env *lst)
{
	size_t	lst_len;

	lst_len = 0;
	while (lst && lst->next != NULL)
	{
		if (lst->value != NULL)
		{
			lst_len += ft_strlen(lst->value);
			lst_len++;
		}
		lst = lst->next;
	}
	return (lst_len);
}
int	ft_strisnum(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

char		*path_join(const char *s1, const char *s2)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(s1, "/");
	path = ft_strjoin(tmp, s2);
	ft_memdel(tmp);
	return (path);
}

char *check_route(char *bin, char *command)
{
	DIR	*folder;
	struct dirent	*content;
	char	*path;

	path = NULL;
	folder = opendir(bin);
	if (!folder)
		return (path);
	while ((content = readdir(folder)))
	{
		if (ft_strcmp(content->d_name, command) == 0)
			path = path_join(bin, content->d_name);
	}
	closedir(folder);
	return (path);
}

char			*env_to_str(t_env *lst)
{
	char	*env;
	int		i;
	int		j;

	if (!(env = malloc(sizeof(char) * size_env(lst) + 1)))
		return (NULL);
	i = 0;
	while (lst && lst->next != NULL)
	{
		if (lst->value != NULL)
		{
			j = 0;
			while (lst->value[j])
			{
				env[i] = lst->value[j];
				i++;
				j++;
			}
		}
		if (lst->next->next != NULL)
			env[i++] = '\n';
		lst = lst->next;
	}
	env[i] = '\0';
	return (env);
}

int			error_message(char *path)
{
	DIR	*folder;
	int	fd;
	int	ret;

	fd = open(path, O_WRONLY);
	folder = opendir(path);
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(path, STDERR);
	if (ft_strchr(path, '/') == NULL)
		ft_putendl_fd(": command not found", STDERR);
	else if (fd == -1 && folder == NULL)
		ft_putendl_fd(": No such file or directory", STDERR);
	else if (fd == -1 && folder != NULL)
		ft_putendl_fd(": is a directory", STDERR);
	else if (fd != -1 && folder == NULL)
		ft_putendl_fd(": Permission denied", STDERR);
	if (ft_strchr(path, '/') == NULL || (fd == -1 && folder == NULL))
		ret = UNKNOWN_COMMAND;
	else
		ret = DIRECTORY;
	if (folder)
		closedir(folder);
	ft_close(fd);
	return (ret);
}

int			cmd_execution(char *path, char **args, t_env *env, t_mini *mini)
{
	char	**env_array;
	char	*ptr;
	int		ret;
	pid_t pid;

	ret = SUCCESS;
	pid = fork();
	if (pid == 0)
	{
		ptr = env_to_str(env);
		env_array = ft_split(ptr, '\n');
		ft_memdel(ptr);
		if (ft_strchr(path, '/') != NULL)
			execve(path, args, env_array);
		ret = error_message(path);
		free_tab(env_array);
		free_token(mini->token);
		exit(ret);
	}
	else
		waitpid(pid, &ret, 0);
	//Control de señales
	return (ret);
}

int	cmd_bin(char **cmd, t_env *env, t_mini *mini)
{
	int i;
	char *path;
	char **route;
	int ret;

	i = 0;
	ret = UNKNOWN_COMMAND;
	while (env && env->value && ft_strncmp(env->value, "PATH=", 5) != 0)
	{
		env = env->next;
	}
	if (env == NULL || env->next == NULL)
	//hacer el control de errores en caso de que nos quiten las variables de entorno(gestion de errores).
		return (cmd_execution(cmd[0], cmd, env, mini));
	route = ft_split(env->value, ':');
	if (!cmd[0] && !route[0])
		return (ERROR);
	i = 1;
	path = check_route(route[0] + 5, cmd[0]);
	while (cmd[0] && route[i] && path == NULL)
		path = check_route(route[i++], cmd[0]);
	if (path != NULL)
		ret = cmd_execution(path, cmd, env, mini);
	else
		ret = cmd_execution(cmd[0], cmd, env, mini);
	free_tab(route);
	ft_memdel(path);
	return (ret);
}

//En caso de tener una variable que guarde datos o tener un valor especial como ? o $, se abre y guarda elll valor real.

char			*expansions(char *arg, t_env *env, int ret)
{
	t_expansions	ex;
	int				new_arg_len;

	new_arg_len = arg_alloc_len(arg, env, ret);
	if (!(ex.new_arg = malloc(sizeof(char) * new_arg_len + 1)))
		return (NULL);
	ex.i = 0;
	ex.j = 0;
	while (ex.i < new_arg_len && arg[ex.j])
	{
		while (arg[ex.j] == EXPANSION)
		{
			ex.j++;
			if ((arg[ex.j] == '\0' || ft_isalnum(arg[ex.j]) == 0)
				&& arg[ex.j] != '?')
				ex.new_arg[ex.i++] = '$';
			else
				insert_var(&ex, arg, env, ret);
		}
		ex.new_arg[ex.i++] = arg[ex.j++];
	}
	ex.new_arg[ex.i] = '\0';
	return (ex.new_arg);
}

//Comprobar que el prompt no tenga pipes

int		has_pipe(t_token *token)
{
	while (token && is_type(token, END) == 0)
	{
		if (is_type(token, PIPE))
			return (1);
		token = token->next;
	}
	return (0);
}

//salida del programar por exit

void	mini_exit(t_mini *mini, char **cmd)
{
	mini->exit = 1;
	ft_putstr_fd("exit ", STDERR);
	if ((cmd[1] && cmd[2]) && (ft_strisnum(cmd[1]) || ft_strisnum(cmd[2])))
	{
		mini->ret = 1;
		ft_putendl_fd("minishell: exit: too many arguments", STDERR);
		mini->exit = 0;
	}
	else if (cmd[1] && cmd[2])
	{
		mini->ret = 255;
		ft_putstr_fd("minishell: exit: ", STDERR);
		ft_putstr_fd(cmd[1], STDERR);
		ft_putendl_fd(": numeric argument required", STDERR);
	}
	else if (cmd[1])
		mini->ret = ft_atoi(cmd[1]);
	else
		mini->ret = 0;
}

int	ft_compare(const char *src1, char *word)
{
	int		i;
	char	*src;

	src = ft_strdup(src1);
	i = 0;
	while (word[i] && src[i])
	{
		if (word[i] != ft_tolower(src[i]))
		{
			return (1);
		}
		i++;
	}
	free(src);
	return (0);
}

//comprueba si es algun ejecutable 

int		is_builtin(char *command)
{
	if (ft_compare(command, "echo") == 0)
		return (1);
	if (ft_strcmp(command, "cd") == 0)
		return (1);
	if (ft_strcmp(command, "pwd") == 0)
		return (1);
	if (ft_compare(command, "env") == 0)
		return (1);
	if (ft_strcmp(command, "export") == 0)
		return (1);
	if (ft_strcmp(command, "unset") == 0)
		return (1);
	return (0);
}

//Ejecuta el comando

int		exec_builtin(char **args, t_mini *mini)
{
	int		result;

	result = 0;
	if (ft_compare(args[0], "echo") == 0)
		result = ft_echo(args);
	if (ft_strcmp(args[0], "pwd") == 0)
		result = ft_pwd();
	if (ft_compare(args[0], "env") == 0)
		result = ft_env(mini->env);
	if (ft_strcmp(args[0], "export") == 0)
		result = ft_export(args, mini->env);
	if (ft_strcmp(args[0], "cd") == 0)
		result = ft_cd(args, mini->env);
	if (ft_strcmp(args[0], "unset") == 0)
		result = ft_unset(args, mini);
	return (result);
}

//Libera el espacio reservado para el argumento en cuestion

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i])
			ft_memdel(tab[i]);
		i++;
	}
	if (tab)
		ft_memdel(tab);
}

//Descompone y guarda los cmd por posicion

char	**cmd_tab(t_token *start)
{
	t_token	*token;
	char	**tab;
	int		i;

	if (!start)
		return (NULL);
	token = start->next;
	i = 2;
	while (token && token->type < TRUNC)
	{
		token = token->next;
		i++;
	}
	if (!(tab = malloc(sizeof(char *) * i)))
		return (NULL);
	token = start->next;
	tab[0] = start->str;
	i = 1;
	while (token && token->type < TRUNC)
	{
		tab[i++] = token->str;
		token = token->next;
	}
	tab[i] = NULL;
	return (tab);
}