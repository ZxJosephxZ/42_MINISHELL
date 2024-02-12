/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseph <joseph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:51:19 by jpajuelo          #+#    #+#             */
/*   Updated: 2024/02/12 13:59:54 by joseph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int check_struct(t_mini *mini, t_token *token)
{
	while (token)
	{
		if (is_types(token, "TAI") && (!token->next || is_types(token->next, "TAIPE")))
		{
			ft_putstr_fd("BRO ESCRIBE BIEN1\n",2);
			mini->error = 258;
			return (0);
		}
		if (is_types(token, "PE") && (!token->prev || token->next || is_types(token->prev, "TAIPE")))
		{
			ft_putstr_fd("BRO ESCRIBE BIEN2\n",2);
			mini->error = 258;
			return (0);
		}
		token = token->next;
	}
	return (1);
}

void execution(t_mini *mini)
{
	t_token *token;
	//int status;
	
	token = next_exe(mini->token, 0);
	if (is_types(mini->token, "TAI"))
	{
		token = mini->token->next;
	}
	else
	{
		token = token;
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
	line = malloc(sizeof(char) * 22);
	line = "cat Makefile | wc -l";
	mini.env = malloc(sizeof(t_env));
	get_env(&mini, envp);
	increment_shlv(mini.env);
	mini.token = get_tokens(line);
	parse_token(&mini);
	token = mini.token;
	while (token)
	{
		if (is_type(token, 8))
		{
			type_token(token, 0);
		}
		token = token->next;
	}
	printf("%s\n",mini.env->value);
	printf("%s\n",mini.env->next->value);
	printf("%s\n",mini.token->str);
	printf("%i\n",mini.token->type);
	printf("%s\n",mini.token->next->str);
	printf("%i\n",mini.token->next->type);
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
