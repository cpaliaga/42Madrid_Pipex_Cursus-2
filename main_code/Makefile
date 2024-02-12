# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caliaga- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/18 14:41:58 by caliaga-          #+#    #+#              #
#    Updated: 2023/12/18 14:55:23 by caliaga-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#### MACROS ####
SRC_DIR = ./srcs/
SRC_FILES = pipex.c utils.c libft.a
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

LIBA_DIR = ./libft/
LIBA_FILES = libft.a
LIBA = $(addprefix $(LIBA_DIR), $(LIBA_FILES))

INC_DIR = ./includes/
INC_FILES = pipex.h
LIB = $(addprefix $(INC_DIR), $(INC_FILES))

OBJ = $(subst .c,.o,$(SRC))

CFLAGS = -Wall -Wextra -Werror 
EFLAGS  = -pedantic -fsanitize=address -g3
NAME = pipex

#### REGLAS ####
all: $(NAME)

$(NAME): $(OBJ)
	make all -C libft
	gcc $(CFLAGS) $(SRCS) $(LIBA) -o $(NAME)
	echo "«$(NAME)» created & indexed"

$(filter-out %.o, $(SRC)): $(filter-out %.c, $(SRC))
	gcc $(CFLAGS) -I$(INC_DIR) -c $^ -o $@

clean:
	@make fclean -C libft
	@rm -fr $(SRC:.c=.o)
	echo "OBJECTS deleted"

fclean: clean
	@rm -fr $(NAME)
	@make clean -C libft
	echo "«$(NAME)» deleted"

re: fclean all bonus

.PHONY: all clean fclean re