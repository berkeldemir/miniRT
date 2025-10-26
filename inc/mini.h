#ifndef MINI_H
# define MINI_H

# include <X11/keysym.h>
# include <X11/X.h>
# include <stdio.h>
# include <fcntl.h>
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
# define ERR_OPENFAIL " File open failed! "

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
char		*get_next_line(int fd);

// parse.c
int			parse_input(char *line);

// parse_objects.c
int			parse_ambient(char **tokens);
int			parse_camera(char **tokens);
int			parse_light(char **tokens);
int			parse_sphere(char **tokens);
int			parse_plane(char **tokens);
int			parse_cylinder(char **tokens);

// free.c
void		free_split(char **split);
#endif