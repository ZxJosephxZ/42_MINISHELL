/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:54:07 by joseph            #+#    #+#             */
/*   Updated: 2024/04/15 10:52:37 by jpajuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

//Buscar los comandos o argumentos ejecutables anteriores

t_token	*prev_token(t_token *token, int skip)
{
	if (token && skip)
	{
		token = token->prev;
	}
	while (token && token->type < TRUNC)
	{
		token = token->prev;
	}
	return (token);
}

//Buscar los comandos o argumentos ejecutables posteriores

t_token	*next_node_token(t_token *token, int skip)
{
	if (token && skip)
	{
		token = token->next;
	}
	while (token && token->type < TRUNC)
	{
		token = token->next;
	}
	return (token);
}

//Mostrar si es el tipo indicado

int	is_type(t_token *token, int arguments)
{
	if (token && token->type == arguments)
	{
		return (1);
	}
	return (0);
}

//Identificar el tipo de ejecucion del comando

int	is_types(t_token *token, char *types)
{
	if (ft_strchr(types, ' ') && is_type(token, EMPTY))
	{
		return (1);
	}
	else if (ft_strchr(types, 'X') && is_type(token, CMD))
	{
		return (1);
	}
	else if (ft_strchr(types, 'x') && is_type(token, ARG))
	{
		return (1);
	}
	else if (ft_strchr(types, 'T') && is_type(token, TRUNC))
	{
		return (1);
	}
	else if (ft_strchr(types, 'A') && is_type(token, APPEND))
	{
		return (1);
	}
	else if (ft_strchr(types, 'I') && is_type(token, INPUT))
	{
		return (1);
	}
	else if (ft_strchr(types, 'P') && is_type(token, PIPE))
	{
		return (1);
	}
	else if (ft_strchr(types, 'E') && is_type(token, END))
	{
		return (1);
	}
	return (0);
}

//Verfica si el comando esta dentro de los tipos designados

int	valid_argument(t_token *token)
{
	t_token	*prev;

	if (!token || is_type(token, CMD) || is_type(token, ARG))
	{
		prev = prev_token(token, NOSKIP);
		if (!prev || is_type(prev, END) || is_type(prev, PIPE))
		{
			return (1);
		}
		return (0);
	}
	else
	{
		return (0);
	}
}

//Comprobar que cumplen un correcto ordenamiento de ejecucion 

void	parse_token(t_mini *mini)
{
	t_token	*token;
	t_token	*prev;

	token = mini->token;
	while (token)
	{
		prev = prev_token(token, NOSKIP);
		if (is_type(token, ARG) && is_types(prev, "TAI"))
		{
			while(valid_argument(prev) == 0)
			{
				prev = prev->prev;
			}
			token->prev->next = token->next;
			if (token->next)
			{
				token->next->prev = token->prev;
			}
			token->prev = prev;
			if (prev)
			{
				token->next = prev->next;
			}
			else
			{
				token->next = mini->token;
				prev = token;
			}
			prev->next->prev = token;
			if (mini->token->prev)
			{
				prev->next = prev->next;
				mini->token = mini->token->prev;
			}
			else
			{
				prev->next = token;
				mini->token = mini->token;
			}
		}
		token = token->next;
	}
}