# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: druina <druina@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/12 14:04:44 by druina            #+#    #+#              #
#    Updated: 2023/01/25 11:25:50 by druina           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC = pipex.c processes.c enviroment.c pipes_and_pid.c

MANPATH = $(addprefix ./mandatory/, $(SRC))

BONUSSRC = pipex_bonus.c processes_bonus.c enviroment_bonus.c pipes_and_pid_bonus.c here_doc_bonus.c

BONUSPATH = $(addprefix ./bonus/, $(BONUSSRC))

FLAGS = -Wall -Wextra -Werror

HEADER = ./mandatory/pipex.h

BONUSHEADER = ./bonus/pipex_bonus.h

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(MANPATH)
	@cd libft && make
	@cd libft && mv libft.a ..
	@cc $(FLAGS) -o $(NAME) $(MANPATH) libft.a -I $(HEADER)

bonus: $(NAME)
	@cd libft && make
	@cd libft && mv libft.a ..
	@cc $(FLAGS) -o $(NAME) $(BONUSPATH) libft.a -I $(BONUSHEADER)

clean:
	@cd libft && make clean
	@rm -f libft.a



fclean: clean
	@rm -f $(NAME)
	@cd libft && make fclean



re: fclean all


