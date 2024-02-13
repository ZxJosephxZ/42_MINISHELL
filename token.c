/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:21:04 by joseph            #+#    #+#             */
/*   Updated: 2024/02/13 12:41:52 by jpajuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int next_alloc(char *line, int *i)
{
    int count;
    int j;
    char c;
    
    count = 0;
    j = 0;
    c = ' ';
    while (line[*i + j] && (line[*i + j] != ' ' || c != ' '))
    {
        if (c == ' ' && (line[*i + j] == '\'' || line[*i + j] == '\"'))
            c = line[*i + j++];
        else if (c != ' ' && line[*i + j] == c)
        {
            count += 2;
            c = ' ';
            j++;
        }
        else
            j++;
        if (line[*i +j - 1] == '\\')
            count--;
    }
    return (j - count + 1);
}

//Aginacion del tipo del token

void type_token(t_token *token, int separator)
{
    if (ft_strcmp(token->str, "") == 0)
        token->type = 1;
    else if (ft_strcmp(token->str, ">") == 0 && separator == 0)
        token->type = 2;
    else if (ft_strcmp(token->str, ">>") == 0 && separator == 0)
        token->type = 3;
    else if (ft_strcmp(token->str, "<") == 0 && separator == 0)
        token->type = 4;
    else if (ft_strcmp(token->str, "|") == 0 && separator == 0)
        token->type = 5;
    else if (ft_strcmp(token->str, ";") == 0 && separator == 0)
        token->type = 6;
    else if(token->prev == NULL || token->prev->type >= 2)
        token->type = 7;
    else
        token->type = 8;
}

//Tomar los argumentos correctamente token por token

t_token *next_token(char *line, int *i)
{
    t_token *token;
    int j;
    int c;
    
    j = 0;
    c = ' ';
    if (!(token = malloc(sizeof(t_token))) || !(token->str = malloc(sizeof(char) * next_alloc(line, i))))
    {
        return (NULL);
    }
    while (line[*i] && (line[*i] != ' ' || c != ' '))
    {
        if (c == ' ' && (line[*i] == '\'' || line[*i] == '\"'))
            c = line[(*i)++];
        else if (c != ' ' && line[*i] == c)
        {
            c = ' ';
            (*i)++;
        }
        else if(line[*i] == '\\' && (*i)++)
        {
            token->str[j++] = line[(*i)++];
        }
        else
            token->str[j++] = line[(*i)++];
    }
    token->str[j] = '\0';
    return (token);
}

//Se salta lo inesesario
static int ignore_sep(char *line, int i)
{
    if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == ';')
        return (1);
    else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '|')
        return (1);
    else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '>')
        return (1);
    else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '>'
            && line[i + 2] && line[i + 2] == '>')
        return (1);
    return (0);
}

//Vamos recorre los tokens y los va añadiendo a la estructura

t_token *get_tokens(char *line)
{
    t_token *next;
    t_token *prev;
    int i;
    int sep;
    
    next = NULL;
    prev = NULL;
    i = 0;
    ft_jump_space(line, &i);
    while (line[i])
    {
        sep = ignore_sep(line, i);
        next = next_token(line, &i);
        next->prev = prev;
        if (prev)
            prev->next = next;
        prev = next;
        type_token(next, sep);
        ft_jump_space(line, &i);
    }
    if (next)
        next->next = NULL;
    while (next && next->prev)
    {
        next = next->prev;
    }
    return next;
}