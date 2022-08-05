NAME = pipex

CC = cc

WFLAGS = -Wall -Werror -Wextra

LIBFT = libft.a

SRC =	pipex.c \
		pipex_utils.c \
		pipex_parsing.c \
		pipex_access_utils.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(WFLAGS) -g3 $(OBJ) -L ./ -lft -o $(NAME)

%.o: %.c
	$(CC) $(WFLAGS) -g3 -c $< -o $@

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
