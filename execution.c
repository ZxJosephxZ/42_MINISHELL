/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseph <joseph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:20:41 by joseph            #+#    #+#             */
/*   Updated: 2024/02/19 19:21:46 by joseph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void ft_close(int fd)
{
    if (fd > 0)
    {
        close(fd);
    }
}

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

void    redirection(t_mini *mini, t_token *token, int type)
{
    ft_close(mini->fdout);
    if (type == TRUNC)
    {
        mini->fdout = open(token->str, O_CREAT | O_WRONLY | O_TRUNC);
    }
    else
    {
        mini->fdout = open(token->str, O_CREAT | O_WRONLY | O_APPEND);
    }
    if (mini->fdout == -1)
    {
        ft_putstr_fd("MINISHELL:", STDERR);
        ft_putstr_fd(token->str, STDERR);
        ft_putstr_fd("No esta pipi pi", STDERR);
        mini->ret = 1;
        mini->not_exec = 1;
        return ;
    }
    dup2(mini->fdout, STDOUT);
}

void    input(t_mini *mini, t_token *token)
{
    ft_close(mini->fdin);
    mini->fdin = open(token->str, O_RDONLY);
    if (mini->fdin == -1)
    {
        ft_putstr_fd("MINISHELL:", STDERR);
        ft_putstr_fd(token->str, STDERR);
        ft_putstr_fd("No esta pipi pi", STDERR);
        mini->ret = 1;
        mini->not_exec = 1;
        return ;
    }
    dup2(mini->fdin, STDIN);
}

int minpipe(t_mini *mini)
{
    pid_t pid;
    int pipefd[2];
    
    pipe(pipefd);
    pid = fork();
    if (pid == 0)
    {
        ft_close(pipefd[1]);
        dup2(pipefd[0], STDIN);
        mini->pipein = pipefd[0];
        mini->pid = -1;
        mini->parent = 0;
        mini->not_exec = 0;
        return (2);
    }
    else
    {
        ft_close(pipefd[0]);
        dup2(pipefd[1], STDOUT);
        mini->pipeout = pipefd[1];
        mini->pid = pid;
        mini->last = 0;
        return (1);
    }
}

void type_exe(t_mini *mini,t_token *token)
{
    //Nodos para poder mover
    t_token *prev;
    t_token *next;
    int pipe;
    
    prev = prev_token(token, 0);
    next = next_node_token(token, 0);
    pipe = 0;
    if (is_type(prev, TRUNC))
    {
        redirection(mini, token, TRUNC);
    }
    else if (is_type(prev,APPEND))
    {
        redirection(mini, token, APPEND);
    }
    else if (is_type(prev,INPUT))
    {
        input(mini,token);
    }
    else if (is_type(prev,PIPE))
    {
        pipe = minpipe(mini);
    }
    if (next && is_type(next, END) == 0 && pipe != 1)
    {
        type_exe(mini, next->next);
    }
    if ((is_type(prev,END) || is_type(prev, PIPE) || !prev) && pipe != 1 )
    {
        //Tratar de ejcutar todos los cmd posibles;
    }
}