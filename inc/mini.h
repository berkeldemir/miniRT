#ifndef MINI_H
# define MINI_H

# include <X11/keysym.h>
# include <X11/X.h>
# include <stdio.h>
# include <unistd.h>
# include "./mlx/mlx.h"
# include "./libft/include/libft.h"

# define FAIL 1
# define SUCCESS 0
# define TRUE 0
# define FALSE 1

# define COLOR_RED "\e[0;101m"
# define COLOR_RESET "\e[0m"

# define MSG_OK ""
# define ERR_CALLOCFAIL " Calloc failed! "
# define ERR_WRONG_ARGS " Arguments are wrong! "
# define ERR_INITIALIZE " Initialization failed, somehow. "

# define W 800
# define H 600
# define TITLE "miniRT"

typedef struct	s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	void	*ptr;

	int		bpp;
	int		sizeline;
	int		endian;
}	t_mlx;

typedef struct	s_mini
{
	t_mlx	mlx;
	char	*file_name;
}	t_mini;

t_mini		*mini(void);
int			arg_control(int ac, char **av);
int			start_hooks(void);
void		quit(char *msg, int retval);

#endif