#ifndef MINI_H
# define MINI_H

# include <X11/keysym.h>
# include <X11/X.h>
# include <stdio.h>
# include <stdint.h>
# include <limits.h>
# include <float.h>
# include <fcntl.h>
# include <unistd.h>
# include "./mlx/mlx.h"
# include "./libft/include/libft.h"

# define FAIL 1
# define SUCCESS 0

# define COLOR_RED "\e[0;101m"
# define COLOR_RESET "\e[0m"

# define MSG_OK ""
# define ERR_CALLOCFAIL " Calloc failed! "
# define ERR_WRONG_ARGS " Arguments are wrong! "
# define ERR_INITIALIZE " Initialization failed, somehow. "
# define ERR_OPENFAIL " File open failed! "
# define ERR_PARSEFAIL " Parse failed! "

# define W 800
# define H 600
# define TITLE "miniRT"

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct	s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef union u_color
{
	uint32_t	value;
	struct
	{
		unsigned char	b;
		unsigned char	g;
		unsigned char	r;
		unsigned char	a;
	};
}	t_color;

typedef struct	s_ambient
{
	double	ratio; // [0.0,1.0]
	t_color	color;
}	t_ambient;

typedef struct	s_camera
{
	t_vec3	coords;
	t_vec3	normals; // [-1,1] for each x,y,z.
	int		h_degree; // [0,180] A.K.A. "FOV".
}	t_camera;

typedef struct	s_light
{
	t_vec3	coords;
	double	brightness; // [0.0, 1.0]
	t_color	color;
}	t_light;

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
	t_mlx		mlx;
	char		*file_name;
	t_ambient	a;
	t_camera	c;
	t_light		l;
	t_bool		a_set;
	t_bool		c_set;
	t_bool		l_set;
	t_list		objs;
}	t_mini;

t_mini		*mini(void);
int			arg_control(int ac, char **av);
int			start_hooks(void);
void		quit(char *msg, int retval);
char		*get_next_line(int fd);

// parser.c
void		free_split(char **split);
void		parser(void);

// parse_objects.c
int			parse_ambient(char ***tokens);
int			parse_camera(char ***tokens);
int			parse_light(char ***tokens);
int			parse_sphere(char ***tokens);
int			parse_plane(char ***tokens);
int			parse_cylinder(char ***tokens);

// free.c

// utils.c
int	assign_color(t_color *ptr, char *color);
int	assign_coords(t_vec3 *ptr, char *coords, t_bool limit_one);

// rt_converters.c
int	rt_atoi(char *str, int min, int max, void *put);
int	rt_atod(char *str, double min, double max, void *put);

#endif