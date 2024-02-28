# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caliaga- <caliaga-@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/18 14:41:58 by caliaga-          #+#    #+#              #
#    Updated: 2024/02/28 18:41:41 by caliaga-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#### MACROS ####
SRC_DIR = ./srcs/
SRC_FILES = pipex.c util_error.c util_path..c util_split_reel.c
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

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
	@rm -fr $(SRC:.c=.o)
	echo "OBJECTS deleted"

fclean: clean
	@rm -fr $(NAME)
	echo "«$(NAME)» deleted"

re: fclean all

.PHONY: all clean fclean re