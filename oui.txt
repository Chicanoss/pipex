NAME = pipex

NAME_BONUS = pipex_bonus

SRCS =	SRCS/pipex.c \
		SRCS/pipex_utils.c \
		SRCS/pipex_conditions.c \
		SRCS/ft_split.c

SRCS_BONUS =	SRCS_bonus/pipex_bonus.c \
				SRCS_bonus/pipex_utils_bonus.c \
				SRCS_bonus/pipex_conditions_bonus.c \
				SRCS_bonus/ft_split_bonus.c \

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

HEADER = incs/pipex.h \

HEADER_BONUS = incs_bonus/pipex_bonus.h \

CC = gcc

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o : %.c $(HEADER) Makefile
	$(CC) $(FLAGS) -I includes -c $< -o $(<:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS) $(HEADER_BONUS) Makefile
	$(CC) $(OBJS_BONUS) -o $(NAME_BONUS)
 
clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY:	all bonus clean fclean re