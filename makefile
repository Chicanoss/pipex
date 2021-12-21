# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/21 14:59:20 by rgeral            #+#    #+#              #
#    Updated: 2021/12/21 15:00:40 by rgeral           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=pipex.a
CC=gcc
CFLAGS=-Wall -Wextra -Werror
RM=rm -f
SRC = pipex.c\
pipex_utils.c\

OBJ = $(SRC:.c=.o)
HEADER_FILE = pipex.h

all: $(NAME)

$(NAME): $(OBJ) $(HEADER_FILE)
	ar rcs $(NAME) $(OBJ)

%.o: %.c $(HEADER_FILE)
	$(CC) $(CFLAGS) -I. -c $< -o $@

clean:
	$(RM) $(OBJ) $(OBJS_B)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean all re