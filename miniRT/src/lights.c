/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:20:54 by beldemir          #+#    #+#             */
/*   Updated: 2025/12/09 19:50:31 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini.h"

static unsigned char	compress(double value)
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

	res.r = compress(color.r * \
		(intensity + (mini()->a.ratio * mini()->a.color.r / 255)));
	res.g = compress(color.g * \
		(intensity + (mini()->a.ratio * mini()->a.color.g / 255)));
	res.b = compress(color.b * \
		(intensity + (mini()->a.ratio * mini()->a.color.b / 255)));
	return (res);
}

uint32_t	apply_light(t_hit hit)
{
	t_vec3	l_dir;
	double	diffuse;

	l_dir = v3_calc_normalize(v3_calc2(mini()->l.coords, '-', hit.point));
	diffuse = v3_calc2_dotprod(hit.normal, l_dir);
	if (diffuse < 0)
		diffuse = 0.0;
	if (mini()->shadows == ON && is_in_shadow(hit) == TRUE)
		diffuse = 0.0;
	diffuse = diffuse * mini()->l.brightness;
	return (get_final_color(hit.obj->color, diffuse).value);
}
