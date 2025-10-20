CC         = cc
CFLAGS     = -Wall -Wextra -Werror -g

LIBFTPATH  = ./inc/libft
LIBFTFLAGS = -L$(LIBFTPATH) -lft

MLXPATH    = ./inc/mlx
MLXFLAGS   = -L$(MLXPATH) -lmlx -lXext -lX11 -lm

NAME       = miniRT
SRCS       = ./src/main.c \
			./src/helpers.c \
			./src/hooks.c
OBJS       = $(SRCS:.c=.o)

all: libft $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLXFLAGS) $(LIBFTFLAGS)

mlx:
	@make -C $(MLXPATH)

libft:
	@make -C $(LIBFTPATH)

clean:
	rm -f $(NAME)

fclean: clean
	rm -f $(OBJS)

ffclean: fclean
	make fclean -C $(LIBFTPATH)

re: fclean all

.PHONY: mlx libft all clean fclean ffclean re