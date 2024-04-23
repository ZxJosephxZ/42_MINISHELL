/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:51:19 by jpajuelo          #+#    #+#             */
/*   Updated: 2024/04/23 14:11:17 by jpajuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

char	*space_line(char *line)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = space_alloc(line);
	while (new && line[i])
	{
		if (quotes(line, i) != 2 && line[i] == '$' && i && line[i - 1] != '\\')
			new[j++] = (char)(-line[i++]);
		else if (quotes(line, i) == 0 && is_sep(line, i))
		{
			new[j++] = ' ';
			new[j++] = line[i++];
			if (quotes(line, i) == 0 && line[i] == '>')
				new[j++] = line[i++];
			new[j++] = ' ';
		}
		else
			new[j++] = line[i++];
	}
	new[j] = '\0';
	ft_memdel(line);
	return (new);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env && env->next)
	{
		tmp = env;
		env = env->next;
		ft_memdel(tmp->value);
		ft_memdel(tmp);
	}
	ft_memdel(env->value);
	ft_memdel(env);
}

void	reset_std(t_mini *mini)
{
	dup2(mini->in, STDIN);
	dup2(mini->out, STDOUT);
}

void	close_fds(t_mini *mini)
{
	ft_close(mini->fdin);
	ft_close(mini->fdout);
	ft_close(mini->pipein);
	ft_close(mini->pipeout);
}

void	reset_fds(t_mini *mini)
{
	mini->fdin = -1;
	mini->fdout = -1;
	mini->pipein = -1;
	mini->pipeout = -1;
	mini->pid = -1;
}
void	free_token(t_token *start)
{
	while (start && start->next)
	{
		ft_memdel(start->str);
		start = start->next;
		ft_memdel(start->prev);
	}
	if (start)
	{
		ft_memdel(start->str);
		ft_memdel(start);
	}
}

void	handle_signal(int sign)
{
	if(sign == SIGINT)
	{
		printf("\n");
	}
}

void    signal_detecter(void)
{
	//SIGINT es la señal cntrl + c
    signal(SIGINT, handle_signal);
	//SIG_ING ignora la señal en este caso cntrl + "\"
    signal(SIGQUIT, SIG_IGN);
}

//Parte que corresponde con la ejecucion de los tokens 
void execution(t_mini *mini)
{
	t_token *token;
	int status;
	
	token = next_exe(mini->token, NOSKIP);
	if (is_types(mini->token, "TAI"))
	{
		token = mini->token->next;
	}
	while (token && mini->exit == 0)
	{
		//ojo pruebas, claro que debemos resetear los fd
		mini->charge = 1;
		mini->last = 1;
		mini->parent = 1;
		type_exe(mini,token);
		reset_std(mini);
		close_fds(mini);
		reset_fds(mini);
		waitpid(-1,&status,0);
		status = WEXITSTATUS(status);
		if (mini->last == 0)
		{
			mini->ret = status;
		}
		if (mini->parent == 0)
		{
			free_token(mini->token);
			exit(mini->ret);
		}
		mini->not_exec = 0;
		token = next_exe(token, SKIP);
	}
}

int	main(int arc, char **argc, char **envp)
{
	t_mini	mini;
	char	*line;

	(void)argc;
	(void)arc;
	mini.in = dup(STDIN);
	mini.out = dup(STDOUT);
	mini.env = malloc(sizeof(t_env));
	mini.ret = 0;
	mini.not_exec = 0;
	mini.exit = 0;
	
	if(arc > 2 && argc == 0)
		return(0);
	//signal_detecter();
	//Obtencion de la variables de entorno
	if (envp[0] == NULL)
	{
		mini.env = getminienv();
	}
	else
	{
		get_env(&mini, envp);
	}
	increment_shlv(mini.env);
	//Particion de los tokens a ejecutar
	
	//Comprobacion de un correcto asignado de tipos o secuencia
	
	while (mini.exit == 0)
	{
		signal_detecter();
		line = readline("Minishell:");
		line = space_line(line); // trampita o.o
		mini.token = get_tokens(line);
		if (mini.token != NULL)
		{
			execution(&mini);
		}
		free_token(mini.token);
	}
	free_env(mini.env);
	return (mini.ret);
}
