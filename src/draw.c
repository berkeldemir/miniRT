#include "../inc/mini.h"

static unsigned int	calculate_pixel_color(int x, int y)
{
	double	fx = (double)x / W;
	double	fy = (double)y / H;

	unsigned char r = (unsigned char)((sin(fx * 2.0 * 3.1415) * 0.5 + 0.5) * 255);
	unsigned char g = (unsigned char)((sin(fy * 2.0 * 3.1415) * 0.5 + 0.5) * 255);
	unsigned char b = (unsigned char)((cos(fabs(fx - fy) * 2.0 * 3.1415) * 0.5 + 0.5) * 255);

	return (r << 16) | (g << 8) | b;
}

int	draw(void)
{
	void	*pixel;
	int		x;
	int		y;

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