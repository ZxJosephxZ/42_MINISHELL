/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 12:41:21 by joseph            #+#    #+#             */
/*   Updated: 2023/11/27 13:56:03 by jpajuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
#include <sys/wait.h>

int     main(int arc, char **argc, char **envp);
void ft_prueba(int numprocess, char **real, char **envp);
void	ft_prueba1(int *fd, int *pipefd, char **real, char **envp);
void	ft_prueba2(int *fd, int *pipefd, char **real, char **envp);
void	execute(char *str, char **envp);
void	error(void);
char	*find_path(char *cmd, char **envp);
void	ft_clean(int i, char **paths);

#endif