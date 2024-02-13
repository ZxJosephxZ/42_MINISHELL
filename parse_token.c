/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:54:07 by joseph            #+#    #+#             */
/*   Updated: 2024/02/13 12:10:09 by jpajuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

t_token *prev_token(t_token *token, int skip)
{
    if (token && skip)
    {
        token = token->prev;
    }
    while (token && token->type < 3)
    {
        token = token->prev;
    }
    return token;
}

int is_type(t_token *token, int arguments)
{
    if (token && token->type == arguments)
    {
        return (1);
    }
    return (0);
}

int is_types(t_token *token, char *types)
{
    if (ft_strchr(types, ' ') && is_type(token, 1))
    {
        return (1);
    }
    else if (ft_strchr(types, 'X') && is_type(token, 7))
    {
        return (1);
    }
    else if (ft_strchr(types, 'x') && is_type(token, 8))
    {
        return (1);
    }
    else if (ft_strchr(types, 'T') && is_type(token, 2))
    {
        return (1);
    }
    else if (ft_strchr(types, 'A') && is_type(token, 3))
    {
        return (1);
    }
    else if (ft_strchr(types, 'I') && is_type(token, 4))
    {
        return (1);
    }
    else if (ft_strchr(types, 'P') && is_type(token, 5))
    {
        return (1);
    }
    else if (ft_strchr(types, 'E') && is_type(token, 6))
    {
        return (1);
    }
    return (0);
}

int valid_argument(t_token *token)
{
    t_token *prev;

    if (!token|| is_type(token, 7) || is_type(token, 8))
    {
        prev = prev_token(token , 0);
        if (!prev || is_type(prev, 6) || is_type(prev, 5))
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

void parse_token(t_mini *mini)
{
    t_token *token;
    t_token *prev;

    token = mini->token;
    while (token)
    {
        prev = prev_token(token,0);
        if (is_type(token, 8) && is_types(prev, "TAI"))
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
                mini->token = mini->token->prev;
            }
            else
            {
                prev->next = token;
            }
        }
        token = token->next;
    }
}