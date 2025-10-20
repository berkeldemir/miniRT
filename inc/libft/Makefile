NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = $(shell find ./src ! -name "ft_lst*.c" -name "ft_*.c")
SRCS_BONUS = $(shell find ./src -name "ft_lst*.c")
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		ar rcs $(NAME) $(OBJS)

bonus: $(OBJS_BONUS)
		ar rcs $(NAME) $(OBJS_BONUS)

clean:
		rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus