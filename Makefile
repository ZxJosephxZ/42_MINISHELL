# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/04 15:35:45 by jpajuelo          #+#    #+#              #
#    Updated: 2023/11/27 12:35:44 by jpajuelo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Minishell

SRC = main.c utils.c

CC = gcc

RE = -lreadline

CFLAGS = -Wall -Werror -Wextra -g

RM = rm -f

OBJ = $(SRC:.c=.o)

%.o : %.c
		@$(CC) $(CFLAGS) -c $< -o $@
		

all : $(NAME)

$(NAME) : $(OBJ)
		@make re -C ./libft
		@$(CC) $(OBJ) $(RE) -Llibft -lft -o $(NAME)
		

clean : 
		@make clean -C ./libft
		$(RM) $(OBJ)

fclean : clean
		@make fclean -C ./libft
		$(RM) $(NAME)

re : fclean all