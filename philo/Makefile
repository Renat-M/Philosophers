NAME = philo
HEAD = philo.h
CC = clang
CFLAGS = -Wall -Wextra -Werror
SRC = philo.c init.c life.c utils.c
OBJ = ${SRC:.c=.o}

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

%.o: %.c $(HEAD)
	$(CC) -c $(CFLAGS) $< -o $(<:.c=.o)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re