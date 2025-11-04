CC         = cc
CFLAGS     = -Wall -Wextra -Werror -g

LIBFTPATH  = ./inc/libft
LIBFTFLAGS = -L$(LIBFTPATH) -lft

GNLPATH	   = ./inc/gnl
GNLFILES   = $(GNLPATH)/get_next_line.c \
			$(GNLPATH)/get_next_line_utils.c

MLXPATH    = ./inc/mlx
MLXFLAGS   = -L$(MLXPATH) -lmlx -lXext -lX11 -lm

NAME       = miniRT
SRCS       = $(GNLFILES) \
			./src/main.c \
			./src/helpers.c \
			./src/hooks.c \
			./src/parser.c \
			./src/parse_scene.c \
			./src/parse_objects.c \
			./src/render.c \
			./src/rt_converters.c \
			./src/rt_utils.c \
			./src/v3_helpers.c \

OBJS       = $(SRCS:.c=.o)

all: libft $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLXFLAGS) $(LIBFTFLAGS)

mlx:
	@make -C $(MLXPATH)

libft:
	@make -C $(LIBFTPATH)
	@make bonus -C $(LIBFTPATH)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

ffclean: fclean
	make fclean -C $(LIBFTPATH)

re: fclean all

.PHONY: mlx libft all clean fclean ffclean re