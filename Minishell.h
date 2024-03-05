/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 12:41:21 by joseph            #+#    #+#             */
/*   Updated: 2024/03/05 15:58:32 by jpajuelo         ###   ########.fr       */
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
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <limits.h>
# include <dirent.h>

# define EMPTY 0
# define CMD 1
# define ARG 2
# define TRUNC 3
# define APPEND 4
# define INPUT 5
# define PIPE 6
# define END 7

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define SKIP 1
# define NOSKIP 0
# define EXPANSION 36
# define UNKNOWN_COMMAND 127
# define ERROR 1
# define SUCCESS 0


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
    int fdout;
    int fdin;
    int pipein;
    int parent;
    int in;
    int out;
    int pid;
    int last;
    int pipeout;
    int pipe;
    int ret;
    int not_exec;
    int error;
    int exit;
    int charge;
    struct s_env *env;
    struct s_token *token;
} t_mini;

typedef struct	s_expansions
{
	char			*new_arg;
	int				i;
	int				j;
}	t_expansions;

int     main(int arc, char **argc, char **envp);
t_token *prev_token(t_token *token, int skip);
t_token *next_node_token(t_token *token, int skip);
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
void type_exe(t_mini *mini,t_token *token);
int    get_env(t_mini *minishell, char **envp);
void    increment_shlv(t_env *env);
t_token *next_token(char *line, int *i);
char	**cmd_tab(t_token *start);
char		*get_env_name(char *dest, const char *src);
int next_alloc(char *line, int *i);
char			*expansions(char *arg, t_env *env, int ret);
int		has_pipe(t_token *token);
void	mini_exit(t_mini *mini, char **cmd);
int		is_builtin(char *command);
int		exec_builtin(char **args, t_mini *mini);
char	**cmd_tab(t_token *start);
void	free_tab(char **tab);

int		get_var_len(const char *arg, int pos, t_env *env, int ret);
int		arg_alloc_len(const char *arg, t_env *env, int ret);
void		insert_var(t_expansions *ex, char *arg, t_env *env, int ret);
char	*get_var_value(const char *arg, int pos, t_env *env, int ret);
int		is_env_char(int c);
char	*get_env_value(char *arg, t_env *env);

int				ft_echo(char **args);
int		ft_pwd(void);
int		ft_env(t_env *env);
int		ft_export(char **args, t_env *env);
int	ft_unset(char **args, t_mini *mini);

#endif