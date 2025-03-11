CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
SRC = ft_split.c  utils4.c  pipex.c \
	utils2.c  utils3.c  utils.c
OBJ = $(SRC:.c=.o)
NAME = pipex

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SECONDARY: $(OBJ)
