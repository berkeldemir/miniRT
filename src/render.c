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
		else if (obj->type == CYLINDER)
			intersect_cylinder(ray, obj, &best_hit);
		objs = objs->next;
	}
	return (best_hit);
}

// hesaolabilen ışık yoğunluğuna göre pixel rengini hesaplar
// normmalize edilmiş normal ve ışık yönü vektörlerinin dot product'ını kullanır

static unsigned int	calculate_lighting(t_hit *hit) 
{
	t_light	*light;
	t_vec3	light_dir;
	t_vec3	light_to_surface;
	double	light_distance;
	double	diffuse_intensity;
	unsigned char r, g, b;
	double	ambient_intensity;

	light = &mini()->l;
	ambient_intensity = mini()->a.ratio;
	r = (unsigned char)(hit->obj->color.r * ambient_intensity);
	g = (unsigned char)(hit->obj->color.g * ambient_intensity);
	b = (unsigned char)(hit->obj->color.b * ambient_intensity);
	if (light->isset == TRUE)
	{
		light_to_surface = v3_calc2(light->coords, '-', hit->point);
		light_distance = sqrt(v3_calc2_dotprod(light_to_surface, light_to_surface));
		if (light_distance > 0.0001)
		{
			light_dir = v3_calc_normalize(light_to_surface);
			diffuse_intensity = v3_calc2_dotprod(hit->normal, light_dir);
			if (diffuse_intensity < 0.0)
				diffuse_intensity = 0.0;
			diffuse_intensity *= light->brightness;
			if (ambient_intensity + diffuse_intensity > 1.0)
				diffuse_intensity = 1.0 - ambient_intensity;
			
			r = (unsigned char)(r + (hit->obj->color.r * diffuse_intensity));
			g = (unsigned char)(g + (hit->obj->color.g * diffuse_intensity));
			b = (unsigned char)(b + (hit->obj->color.b * diffuse_intensity));
		}
	}

	return ((unsigned int)r << 16) | ((unsigned int)g << 8) | (unsigned int)b;
}

static unsigned int	calculate_pixel_color(int x, int y)
{
	t_ray	ray;
	t_hit	hit;

	ray = generate_ray_from_pixel(x, y);
	hit = get_hit_record(&ray);

	if (hit.dist < DBL_MAX && hit.obj != NULL)
		return (calculate_lighting(&hit));
	return (0x000000);
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
