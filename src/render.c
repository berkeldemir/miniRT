#include "../inc/mini.h"

static t_ray	generate_ray_from_pixel(int x, int y)
{
	t_ray	ray;
	t_vec3	remap;
	t_vec3	dir; // direction

	// Ray's starting point->camera coordinate.
	ray.origin = mini()->c.coords;

	// Imagine viewpoint as the center point is (0,0)
	// top-left corner is (-1, +1) and
	// bottom-right corner is (+1, -1)
	// remap point is where the spesific point at in this viewpoint
	// and multiplies it by the viewport's ((w or h) / 2)
	// and holds the exact point on viewport of the pixel
	remap.x = ((2.0 * ((x + 0.5) / WD)) - 1.0) * (mini()->c.viewport.x / 2.0);
	remap.y = (1.0 - (2.0 * ((y + 0.5) / HD))) * (mini()->c.viewport.y / 2.0);
	remap.z = 0.0;

	dir = mini()->c.fwd;
	dir = v3_calc2(dir, '+', \
		v3_calc2(mini()->c.right, '*', (t_vec3){remap.x, remap.x, remap.x}));
	dir = v3_calc2(dir, '+', \
		v3_calc2(mini()->c.up, '*', (t_vec3){remap.y, remap.y, remap.y}));
	ray.direction = v3_calc_normalize(dir);
	return (ray);
}

static t_hit	get_hit_record(t_ray *ray)
{
	t_list	*objs;	
	t_obj	*obj;
	t_hit	best_hit;
	
	best_hit.dist = DBL_MAX;
	best_hit.obj = NULL;
	objs = mini()->objs;
	while (objs)
	{
		obj = objs->content;
		if (obj->type == SPHERE)
			intersect_sphere(ray, obj, &best_hit);
		else if (obj->type == PLANE)
			intersect_plane(ray, obj, &best_hit);
		/*else if (obj->type == CYLINDER)
			; //intersect_cylinder(ray, obj, &best_hit);*/
		objs = objs->next;
	}
	return (best_hit);
}

static unsigned int	calculate_pixel_color(int x, int y)
{
	t_ray	ray;
	t_hit	hit;

	ray = generate_ray_from_pixel(x, y);
	hit = get_hit_record(&ray);

	if (hit.dist < DBL_MAX)
		return (hit.obj->color.value);
	
	double	fx = (double)x / W;
	double	fy = (double)y / H;

	unsigned char r = (unsigned char)((sin(fx * 2.0 * 3.1415) * 0.5 + 0.5) * 255);
	unsigned char g = (unsigned char)((sin(fy * 2.0 * 3.1415) * 0.5 + 0.5) * 255);
	unsigned char b = (unsigned char)((cos(fabs(fx - fy) * 2.0 * 3.1415) * 0.5 + 0.5) * 255);

	return (r << 16) | (g << 8) | b;
	// return(0x000000); // Background is the gradient now.
}

void	setup_camera_basis(void)
{
	t_vec3		w_up;
	t_camera	*c;

	c = &mini()->c;
	c->fwd = c->normal;
	if (c->fwd.x == 0 && c->fwd.z == 0 && \
		(c->fwd.y == 1 || c->fwd.y == -1))
		w_up = v3_new(0.0, 0.0, 1.0);
	else
		w_up = v3_new(0.0, 1.0, 0.0);
	c->right = v3_calc_normalize(v3_calc2_cross(w_up, c->fwd));
	c->up = v3_calc_normalize(v3_calc2_cross(c->fwd, c->right));
	return ;
}

void	setup_viewport(void)
{
	double	h_degree_radiant;

	h_degree_radiant = mini()->c.h_degree * (3.1415 / 180.0) / 2.0;
	mini()->c.viewport.y = 2.0 * tan(h_degree_radiant);
	mini()->c.viewport.x = mini()->c.viewport.y * (WD / HD);
	mini()->c.viewport.z = 0.0;
	return ;
}

int	render(void)
{
	void	*pixel;
	int		x;
	int		y;

	setup_camera_basis();
	setup_viewport();
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
		mini()->mlx.img, 0, 0);
	return (SUCCESS);
}
