/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:51:19 by jpajuelo          #+#    #+#             */
/*   Updated: 2024/02/13 12:40:39 by jpajuelo         ###   ########.fr       */
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
			ft_putstr_fd("BRO ESCRIBE BIEN1\n",2);
			mini->error = 2;
			return (0);
		}
		if (is_types(token, "PE") && (!token->prev || !token->next || is_types(token->prev, "TAIPE")))
		{
			ft_putstr_fd("BRO ESCRIBE BIEN2\n",2);
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
	//int status;
	
	token = next_exe(mini->token, 0);
	if (is_types(mini->token, "TAI"))
	{
		token = mini->token->next;
	}

	//Procesos
}

int	main(int arc, char **argc, char **envp)
{
	//char	*prompt;
	//char	**real;
	//int		numprocess;
	t_mini mini;
	t_token *token;
	char *line;

	(void)argc;
	(void)arc;
	// reserva de una linea pero aqui usaremos el readline
	line = malloc(sizeof(char) * 22);
	line = "$ARG=Makefile | cat $ARG | wc -l";
	mini.env = malloc(sizeof(t_env));
	//Obtencion de la variables de entorno
	get_env(&mini, envp);
	//La incrementacion de la env shlvl para cada proceso en ejecucion
	increment_shlv(mini.env);
	//Particion de los tokens a ejecutar
	mini.token = get_tokens(line);
	//Comprobacion de un correcto asignado de tipos o secuencia
	parse_token(&mini);
	//Variable auxiliar que servira como nodo para la estructura de cola de los tokens
	token = mini.token;

	/**while (token)
	{
		if (is_type(token, 8))
		{
			type_token(token, 0);
		}
		token = token->next;
	}**/
	//Para comprobar los tokens bien divididos con sus respectivos tipos
	while (mini.token)
	{
		printf("---------------------\n");
		printf("%s\n",mini.token->str);
		printf("%i\n",mini.token->type);
		printf("---------------------\n");
		mini.token = mini.token->next;
	}
	//Proceso de ejecucion dependiendo del tipo de token
	if (mini.token != NULL && check_struct(&mini, mini.token))
	{
		execution(&mini);
	}
	
	//numprocess = 1;
	return (0);
	/**while ((prompt = readline("")))
	{
		real = ft_split(prompt, 32);
		free(prompt);
	}**/

}
