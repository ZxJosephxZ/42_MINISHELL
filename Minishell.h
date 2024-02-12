/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseph <joseph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 12:41:21 by joseph            #+#    #+#             */
/*   Updated: 2024/02/12 13:54:08 by joseph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

typedef struct s_env
{
    char *value;
    struct s_env *next;
} t_env;

typedef struct s_token
{
    int i;
    struct s_token *prev;
    struct s_token *next;
    char *str;
    int  type;
} t_token;

typedef struct s_mini
{
    int signin;
    int signout;
    int error;
    struct s_env *env;
    struct s_token *token;
} t_mini;

int     main(int arc, char **argc, char **envp);
void parse_token(t_mini *mini);
void	execute(char *str, char **envp);
t_token *get_tokens(char *line);
void    ft_jump_space(const char *str, int *i);
void	error(void);
int is_types(t_token *token, char *types);
void type_token(t_token *token, int separator);
t_token *next_exe(t_token *token, int skip);
int is_type(t_token *token, int arguments);
char	*find_path(char *cmd, char **envp);
void	ft_clean(int i, char **paths);
int    get_env(t_mini *minishell, char **envp);
void    increment_shlv(t_env *env);
t_token *next_token(char *line, int *i);
int next_alloc(char *line, int *i);
#endif