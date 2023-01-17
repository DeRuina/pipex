# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: druina <druina@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/12 14:04:44 by druina            #+#    #+#              #
#    Updated: 2023/01/17 10:38:01 by druina           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC = pipex.c processes.c

FLAGS = -Wall -Wextra -Werror

HEADER = pipex.h


.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(SRC)
	cd libft && make
	cd libft && mv libft.a ..
	cc $(FLAGS) -o $(NAME) $(SRC) libft.a -I $(HEADER) -g



clean:
	cd libft && make clean
	rm -f libft.a



fclean: clean
	rm -f $(NAME)
	cd libft && make fclean



re: fclean all


