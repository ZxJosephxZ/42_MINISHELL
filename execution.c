/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:20:41 by joseph            #+#    #+#             */
/*   Updated: 2024/02/13 12:31:59 by jpajuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

//ver si el token en cuestion es de tipo ejecutable de lo contrario avanzar al siguiente token

t_token *next_exe(t_token *token, int skip)
{
    if (token && skip)
    {
        token = token->next;
    }
    while (token && token->type != 7)
    {
        token = token->next;
        if ( token && token->type == 7 && token->prev == NULL)
        {
            ;
        }
        else if (token && token->type == 7 && token->type < 6)
        {
            token = token->next;
        }
    }
    return (token);
}