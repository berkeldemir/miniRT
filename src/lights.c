/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:20:54 by beldemir          #+#    #+#             */
/*   Updated: 2025/12/09 14:22:41 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini.h"

static unsigned char	clamp(double value)
{
	if (value > 255.0)
		return (255);
	if (value < 0.0)
		return (0);
	return ((unsigned char)value);
}

static int	is_in_shadow(t_hit hit)
{
	t_ray	shadow_ray;
	t_hit	shadow_hit;
	t_vec3	light_dir;
	double	len_sq;

	light_dir = v3_calc2(mini()->l.coords, '-', hit.point);
	len_sq = v3_calc2_dotprod(light_dir, light_dir);
	shadow_ray.direction = v3_calc_normalize(light_dir);
	shadow_ray.origin = v3_calc2(hit.point, '+', \
		v3_calc2(hit.normal, '*', (t_vec3){0.01, 0.01, 0.01}));
	shadow_hit = get_hit_record(&shadow_ray);
	if (shadow_hit.dist < DBL_MAX \
	&& (shadow_hit.dist * shadow_hit.dist) < len_sq)
		return (TRUE);
	return (FALSE);
}

static t_color	get_final_color(t_color color, double intensity)
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
		diffuse = 0.0;
	if (is_in_shadow(hit) == TRUE)
		diffuse = 0.0;
	diffuse = diffuse * mini()->l.brightness;
	total_intensity = mini()->a.ratio + diffuse;
	return (get_final_color(hit.obj->color, total_intensity).value);
}
