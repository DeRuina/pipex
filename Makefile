# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: druina <druina@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/12 14:04:44 by druina            #+#    #+#              #
#    Updated: 2023/01/24 11:31:28 by druina           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC = pipex.c processes.c enviroment.c pipes_and_pid.c

BONUSSRC = pipex_bonus.c processes_bonus.c enviroment_bonus.c pipes_and_pid_bonus.c here_doc_bonus.c

MPATHDIR = mandatory/

BPATHDIR = bonus/

MPATH = $(addprefix $(MPATHDIR), $(SRC))

BPATH = $(addprefix $(BPATHDIR), $(BONUSSRC))

FLAGS = -Wall -Wextra -Werror

HEADER = pipex.h


.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(SRC)
	@cd libft && make
	@cd libft && mv libft.a ..
	@cc $(FLAGS) -o $(NAME) $(MPATHDIR) $(SRC) libft.a -I $(HEADER)



clean:
	@cd libft && make clean
	@rm -f libft.a



fclean: clean
	@rm -f $(NAME)
	@cd libft && make fclean



re: fclean all


