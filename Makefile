NAME = pipex

CC = cc

WFLAGS = -Wall -Werror -Wextra

LIBFT = libft.a

SRC = pipex.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(WFLAGS) -L ./ -lft -o $(NAME)

%.o: %.c
	$(CC) $(WFLAGS) -c $< -o $@

$(LIBFT):
	make -C libft

re: fclean all

fclean: clean
	rm -rf $(NAME)
	make fclean -C libft

clean:
	rm -rf *.o

.PONHY: re fclean clean all
