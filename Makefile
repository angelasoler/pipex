NAME = pipex

CC = cc

WFLAGS = -Wall -Werror -Wextra

LIBFT = libft.a

SRC =	pipex.c \
		pipex_utils.c \
		pipex_parsing.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(WFLAGS) $(OBJ) -L ./ -lft -o $(NAME)

%.o: %.c
	$(CC) $(WFLAGS) -c $< -o $@

$(LIBFT):
	make -C libft

re: fclean all

fclean: clean
	rm -rf $(NAME)

clean:
	rm -rf *.o

fclean_libft: fclean
	make fclean -C libft

.PONHY: re fclean clean all
