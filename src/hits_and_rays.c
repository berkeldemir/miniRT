/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hits_and_rays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:48:47 by beldemir          #+#    #+#             */
/*   Updated: 2025/12/09 15:03:58 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini.h"

t_hit	get_hit_record(t_ray *ray)
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

t_ray	generate_ray_from_pixel(int x, int y)
{
	t_ray	ray;
	t_vec3	remap;
	t_vec3	dir;

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
