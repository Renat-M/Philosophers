NAME = philo_bonus
HEAD = philo_bonus.h
CC = clang
CFLAGS = -Wall -Wextra -Werror
SRC = philo_bonus.c utils_bonus.c init_bonus.c life_bonus.c
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