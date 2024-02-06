/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseph <joseph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:51:19 by jpajuelo          #+#    #+#             */
/*   Updated: 2024/02/06 17:20:14 by joseph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	main(int arc, char **argc, char **envp)
{
	//char	*prompt;
	//char	**real;
	//int		numprocess;
	t_mini *mini;
	char *line;

	(void)argc;
	(void)arc;
	mini = malloc(sizeof(t_mini));
	if (!mini)
	{
		return (0);
	}
	mini->env = malloc(sizeof(t_env));
	get_env(mini, envp);
	increment_shlv(mini->env);
	mini->token = get_tokens(line);
	printf("%s\n",mini->env->value);
	printf("%s\n",mini->env->next->value);
	//numprocess = 1;
	return (0);
	/**while ((prompt = readline("")))
	{
		real = ft_split(prompt, 32);
		free(prompt);
	}**/

}
