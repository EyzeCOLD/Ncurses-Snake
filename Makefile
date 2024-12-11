# ~~~~~~~~~~~~~ #
# THE SNAKEFILE #
# ~~~~~~~~~~~~~ #

NAME = Snake

SRC = snake.c draw.c

OBJ = $(SRC:.c=.o)

INC = snake.h

LIB = -lcurses

CC = cc

CFLAGS = -Wall -Wextra -Werror

# ~~~~~~~~~~~~~ #

all: $(NAME)

$(NAME): $(OBJ) $(INC)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $@

%.o: %.c $(INC)
	$(CC) $(CFLAGS) -c $< $(LIB) -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
