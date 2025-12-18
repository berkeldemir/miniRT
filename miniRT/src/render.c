/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:27:52 by beldemir          #+#    #+#             */
/*   Updated: 2025/12/09 19:45:38 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini.h"

static unsigned int	calculate_pixel_color(int x, int y)
{
	t_ray	ray;
	t_hit	hit;

	ray = generate_ray_from_pixel(x, y);
	hit = get_hit_record(&ray);
	if (hit.dist < DBL_MAX)
		return (apply_light(hit));
	return (0x000000);
}

void	setup_camera_basis_and_viewport(void)
{
	t_vec3		w_up;
	t_camera	*c;
	double		h_degree_radiant;

	c = &mini()->c;
	c->fwd = c->normal;
	if (c->fwd.x == 0 && c->fwd.z == 0 && \
		(c->fwd.y == 1 || c->fwd.y == -1))
		w_up = v3_new(0.0, 0.0, 1.0); // cross product sonunda  vektör 0,0,0 olmasın diye
	else
		w_up = v3_new(0.0, 1.0, 0.0);
	c->right = v3_calc_normalize(v3_calc2_cross(w_up, c->fwd));
	c->up = v3_calc_normalize(v3_calc2_cross(c->fwd, c->right));
	h_degree_radiant = mini()->c.h_degree * (3.1415 / 180.0) / 2.0;
	mini()->c.viewport.y = 2.0 * tan(h_degree_radiant);
	mini()->c.viewport.x = mini()->c.viewport.y * (WD / HD);
	mini()->c.viewport.z = 0.0;
	return ;
}

static void	render_low_quality(unsigned int color, unsigned int *pixel)
{
	int	i;
	int	j;
	int	sizeline;

	sizeline = mini()->mlx.sizeline / 4;
	j = 0;
	while (j < mini()->render_res)
	{
		i = 0;
		while (i < mini()->render_res)
		{
			*(pixel + i + (j * sizeline)) = color;
			i++;
		}
		j++;
	}
}

int	render(void)
{
	unsigned int	color;
	void			*pixel;
	int				x;
	int				y;

	setup_camera_basis_and_viewport();
	y = 0;
	while (y < H)
	{
		x = 0;
		while (x < W)
		{
			pixel = mini()->mlx.ptr + (y * mini()->mlx.sizeline) + \
			(x * (mini()->mlx.bpp / 8));
			color = calculate_pixel_color(x, y);
			*(unsigned int *)pixel = color;
			if (mini()->render_res == LOW_RES)
				render_low_quality(color, (unsigned int *)pixel);
			x += mini()->render_res;
		}
		y += mini()->render_res;
	}
	return (SUCCESS);
}
