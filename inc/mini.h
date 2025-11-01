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
# include <math.h>
# include "./mlx/mlx.h"
# include "./libft/include/libft.h"

# define FAIL 1
# define SUCCESS 0

# define COLOR_RED "\e[0;101m"
# define COLOR_RESET "\e[0m"

# define MSG_OK ""
# define ERR_CALLOC " Calloc failed! "
# define ERR_ARGS " Arguments are wrong! "
# define ERR_INITIALIZE " Initialization failed! "
# define ERR_OPENFAIL " File open failed! "
# define ERR_PARSE " Parse failed! "
# define ERR_DRAW " Draw failed! "

# define W 800
# define H 600
# define WD 800.00
# define HD 600.00
# define TITLE "miniRT"

# define SPHERE 's'
# define PLANE 'p'
# define CYLINDER 'c'

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
	t_bool	isset;
	double	ratio; // [0.0,1.0]
	t_color	color;
}	t_ambient;

typedef struct	s_camera
{
	t_bool	isset;
	t_vec3	coords;
	t_vec3	normal; // [-1,1] for each x,y,z.
	int		h_degree; // [0,180] A.K.A. "FOV".
}	t_camera;

typedef struct	s_light
{
	t_bool	isset;
	t_vec3	coords;
	double	brightness; // [0.0, 1.0]
	t_color	color;
}	t_light;

/*
typedef struct	s_sphere
{
	t_vec3	coords;
	double	diameter;
	t_color	color;
}	t_sphere;

typedef struct	s_plane
{
	t_vec3	coords;
	t_vec3	normal; // [-1, 1] for each x,y,z.
	t_color	color;
}	t_plane;

typedef struct	s_cylinder
{
	t_vec3	coords;
	t_vec3	normal; // [-1, 1] for each x,y,z.
	double	diameter;
	double	height;
}	t_cylinder;
*/

typedef struct	s_obj
{
	char	type;
	t_vec3	coords;
	t_vec3	normal; // [-1, 1] for each x,y,z.
	double	diameter;
	double	height;
	t_color	color;
}	t_obj;

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
	t_list		*objs;
}	t_mini;

char		*get_next_line(int fd);

// draw.c
int		draw(void);

// helpers.c
t_mini	*mini(void);
int		arg_control(int ac, char **av);
void	quit(char *msg, int retval);

// hooks.c
int		start_hooks(void);

// parse_objects.c
int		parse_sphere(char ***tokens);
int		parse_plane(char ***tokens);
int		parse_cylinder(char ***tokens);

// parse_scene.c
int		parse_ambient(char ***tokens);
int		parse_camera(char ***tokens);
int		parse_light(char ***tokens);

// parser.c
void	free_split(char **split);
int		parser(void);

// rt_converters.c
int		rt_atoi(char *str, int min, int max, void *put);
int		rt_atod(char *str, double min, double max, void *put);

// rt_utils.c
int		rt_color(t_color *ptr, char *color);
int		rt_coords(t_vec3 *ptr, char *coords, t_bool limit_one);
t_vec3	v3_new(double x, double y, double z);

// v3_helpers.c
t_vec3  v3_calc2(t_vec3 a, char operation, t_vec3 b);
double	v3_calc2_dotprod(t_vec3 a, t_vec3 b);
t_vec3	v3_calc_normalize(t_vec3 a);
t_vec3	v3_calc2_crossprod(t_vec3 a, t_vec3 b);

#endif