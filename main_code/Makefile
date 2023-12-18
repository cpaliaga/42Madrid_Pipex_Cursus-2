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

SRC_DIR = ./
SRC_FILES = pipex.c
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

INC_DIR = ./
INC_FILES = pipex.h
LIB = $(addprefix $(INC_DIR), $(INC_FILES))

OBJ = $(subst .c,.o,$(SRC))

CFLAGS = -Wall -Wextra -Werror 
EFLAGS  = -pedantic
NAME = pipex

EXECUTE= .

#### REGLAS ####
all: $(NAME)

$(NAME): $(OBJ)
	ar crs $(NAME) $(OBJ)
	ranlib $(NAME)
	echo "library $(NAME) created & indexed"

$(filter-out %.o, $(SRC)): $(filter-out %.c, $(SRC))
	gcc $(CFLAGS) -I$(INC_DIR) -c $^ -o $@

clean:
	rm -fr $(SRC:.c=.o)
	echo "OBJECTS deleted"

fclean: clean
	@rm -fr $(NAME)
	@echo "$(NAME) deleted"

re: fclean all bonus

.PHONY: all clean fclean re

