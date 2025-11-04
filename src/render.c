#include "../inc/mini.h"

static unsigned int	calculate_pixel_color(int x, int y)
{


	/*
	double	fx = (double)x / W;
	double	fy = (double)y / H;

	unsigned char r = (unsigned char)((sin(fx * 2.0 * 3.1415) * 0.5 + 0.5) * 255);
	unsigned char g = (unsigned char)((sin(fy * 2.0 * 3.1415) * 0.5 + 0.5) * 255);
	unsigned char b = (unsigned char)((cos(fabs(fx - fy) * 2.0 * 3.1415) * 0.5 + 0.5) * 255);

	return (r << 16) | (g << 8) | b;
	*/
}

void	setup_camera_basis(void)
{
	t_vec3		w_up;
	t_camera	*c;

	c = &mini()->c;
	c->fwd = c->normal;
	if (c->fwd.x == 0 && c->fwd.z && \
		(c->fwd.y == 1 || c->fwd.y == -1))
		w_up = v3_new(0.0, 0.0, 1.0);
	else
		w_up = v3_new(0.0, 1.0, 0.0);
	c->right = v3_calc_normalize(v3_calc2_cross(w_up, c->fwd));
	c->up = v3_calc_normalize(v3_calc2_cross(c->fwd, c->right));
}

int	render(void)
{
	void	*pixel;
	int		x;
	int		y;

	setup_camera_basis();
	x = 0;
	while (x < W)
	{
		y = 0;
		while (y < H)
		{
			pixel = mini()->mlx.ptr + \
			(y * mini()->mlx.sizeline) + \
			(x * (mini()->mlx.bpp / 8));
			*(unsigned int *)pixel = calculate_pixel_color(x, y);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(\
		mini()->mlx.mlx, \
		mini()->mlx.win, \
		mini()->mlx.img, \
		0, 0);
	return (SUCCESS);
}
