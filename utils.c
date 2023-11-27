/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 12:27:10 by jpajuelo          #+#    #+#             */
/*   Updated: 2023/11/27 13:48:16 by jpajuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	ft_clean(int i, char **paths)
{
	while (paths[++i])
		free(paths[i]);
	free(paths);
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	if (cmd[0] == '/')
		return (cmd);
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	ft_clean(-1, paths);
	return (0);
}

void	error(void)
{
	perror("ERROR");
	exit(EXIT_FAILURE);
}

void	execute(char *str, char **envp)
{
	int		i;
	char	**cmd;
	char	*path;

	i = -1;
	cmd = ft_split(str, ' ');
	path = find_path(cmd[0], envp);
	if (!path)
	{
		while (cmd[++i])
		{
			free(cmd[i]);
		}
		free(cmd);
		error();
	}
	if (execve(path, cmd, envp) == -1)
	{
		error();
	}
}
