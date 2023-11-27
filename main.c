/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:51:19 by jpajuelo          #+#    #+#             */
/*   Updated: 2023/11/27 13:59:37 by jpajuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	ft_prueba1(int *fd, int *pipefd, char **real, char **envp)
{
	pid_t	acess;

	acess = fork();
	if (acess < 0)
	{
		perror("error en el hijo");
		exit(0);
	}
	else
	{
		fd[0] = open(real[1], O_RDONLY, 0777);
		if (fd[0] < 0)
		{
			perror("error al leer el archivo");
			exit(0);
		}
		else
		{
			close(pipefd[0]);
			dup2(fd[0], STDIN_FILENO);
			dup2(pipefd[1], STDOUT_FILENO);
			execute(real[0], envp);
		}
	}
}

void	ft_prueba2(int *fd, int *pipefd, char **real, char **envp)
{
	pid_t	acess;

	acess = fork();
	if (acess < 0)
	{
		perror("error en el hijo");
		exit(0);
	}
	else
	{
		/*fd[1] = open(argc[3], O_CREAT, O_TRUNC, O_WRONLY, 0777);
		if (fd[1] < 0)
		{
			perror("error al leer el archivo");
			exit(0);
		}
		*/
		fd[1] = open(real[3], O_WRONLY, O_CREAT, O_TRUNC, 0777);
		printf("%s\n", real[2]);
		close(pipefd[1]);
		dup2(fd[1], STDOUT_FILENO);
		dup2(pipefd[0], STDIN_FILENO);
		execute(real[2], envp);
	}
}

void ft_prueba(int numprocess, char **real, char **envp)
{
	int		fd[2];
	int		pipefd[2];
	int		result;

	if (pipe(pipefd) == -1)
	{
		perror("error al realizar el pipe");
		exit(0);
	}
	else
	{
		if (numprocess != 0)
		{
			printf("wntro\n");
			ft_prueba1(fd, pipefd, real, envp);
			ft_prueba2(fd, pipefd, real, envp);
		}
		waitpid(-1, &result, 0);
		waitpid(-1, &result, 0);
	}
}

int	main(int arc, char **argc, char **envp)
{
	char	*prompt;
	char	**real;
	int		numprocess;


	(void)argc;
	(void)arc;
	numprocess = 1;
	while ((prompt = readline("")))
	{
		printf("%s ddd\n", prompt);
		real = ft_split(prompt, 32);
		printf("%s xdd\n", real[1]);
		ft_prueba(numprocess, real, envp);
		free(prompt);
	}

}
