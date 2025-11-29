#include "../inc/mini.h"

static unsigned char    clamp(double value)
{
	if (value > 255.0)
		return (255);
	if (value < 0.0)
		return (0);
	return ((unsigned char)value);
}

static t_color  get_final_color(t_color color, double intensity)
{
	t_color	res;

	res.r = clamp(color.r * intensity);
	res.g = clamp(color.g * intensity);
	res.b = clamp(color.b * intensity);
	return (res);
}

uint32_t	apply_light(t_hit hit)
{
	t_vec3	l_dir;
	double	diffuse;
	double	total_intensity;

	l_dir = v3_calc_normalize(v3_calc2(mini()->l.coords, '-', hit.point));
	diffuse = v3_calc2_dotprod(hit.normal, l_dir);
	if (diffuse < 0)
		diffuse = 0;
	diffuse = diffuse * mini()->l.brightness;
	total_intensity = mini()->a.ratio + diffuse;
	return (get_final_color(hit.obj->color, total_intensity).value);
}