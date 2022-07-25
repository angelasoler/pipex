NAME = ../libft.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra

SRC =	ft_itoa.c \
		ft_toupper.c \
		ft_strlen.c \
		ft_strjoin.c \
		ft_strdup.c \
		ft_split.c \
		ft_calloc.c \
		ft_bzero.c \
		get_next_line.c \
		get_next_line_utils.c \
		ft_printf.c \
		ft_printf_other_convs.c \
		ft_printf_int_convs.c

OBJ=$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ar -r $(NAME) $(OBJ)

%.o: %.c ../includes/libft.h 
	@$(CC) $(CFLAGS) -c $< -I../includes -o $@

re: fclean all

fclean: clean
	rm -rf $(NAME)

clean:
	rm -rf *.o
