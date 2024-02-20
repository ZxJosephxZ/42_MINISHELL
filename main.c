/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:51:19 by jpajuelo          #+#    #+#             */
/*   Updated: 2024/02/20 13:31:46 by jpajuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"


//Comprueba el correcto ordenamiento de los tokens para su posterior ejecucion
//El primer if comprueba tokens vacios y redirecciones
//Ell segundo if hace la comprobacion de pipe y finales como el ;
int check_struct(t_mini *mini, t_token *token)
{
	while (token)
	{
		if (is_types(token, "TAI") && (!token->next || is_types(token->next, "TAIPE")))
		{
			ft_putstr_fd("BRO ESCRIBE BIEN1\n",STDERR);
			mini->error = 2;
			return (0);
		}
		if (is_types(token, "PE") && (!token->prev || !token->next || is_types(token->prev, "TAIPE")))
		{
			ft_putstr_fd("BRO ESCRIBE BIEN2\n",STDERR);
			mini->error = 2;
			return (0);
		}
		token = token->next;
	}
	return (1);
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
		waitpid(-1,&status,0);
		exit(mini->ret);
	}
	//Procesos
}

int	main(int arc, char **argc, char **envp)
{

	t_mini mini;
	char *line;

	(void)argc;
	(void)arc;
	mini.env = malloc(sizeof(t_env));
	mini.ret = 0;
	mini.not_exec = 0;
	mini.exit = 0;
	//Obtencion de la variables de entorno
	get_env(&mini, envp);
	//La incrementacion de la env shlvl para cada proceso en ejecucion
	increment_shlv(mini.env);
	//Particion de los tokens a ejecutar
	
	//Comprobacion de un correcto asignado de tipos o secuencia
	parse_token(&mini);
	while(1)
	{
		line = readline("Minishell:");
		mini.token = get_tokens(line);
		if (mini.token != NULL && check_struct(&mini, mini.token))
		{
			execution(&mini);
		}
	}


}
