/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:18:35 by beldemir          #+#    #+#             */
/*   Updated: 2025/12/09 19:56:49 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini.h"

static double	solve_quad_find_t(t_quad *q)
{
	q->delta = (q->b * q->b) - (4 * q->a * q->c);
	if (q->delta < 0)
		return (0);
	q->t1 = (-(q->b) - sqrt(q->delta)) / (2.0 * q->a);
	q->t2 = (-(q->b) + sqrt(q->delta)) / (2.0 * q->a);
	if (q->t1 > 0.0001 && (q->t1 < q->t2 || q->t2 < 0.0001))
		return (q->t1);
	else if (q->t2 > 0.0001)
		return (q->t2);
	return (0.0);
}

void	intersect_sphere(t_ray *ray, t_obj *obj, t_hit *best_hit)
{
	t_quad	q;
	double	t;
	t_vec3	oc_vector;

	oc_vector = v3_calc2(ray->origin, '-', obj->coords);
	q.a = 1.0;
	q.b = 2.0 * v3_calc2_dotprod(ray->direction, oc_vector);
	q.c = v3_calc2_dotprod(oc_vector, oc_vector);
	q.c -= (obj->diameter * obj->diameter) / 4;
	t = solve_quad_find_t(&q);
	if (t > 0.00 && t < best_hit->dist)
	{
		best_hit->dist = t;
		best_hit->obj = obj;
		best_hit->point = v3_calc2(ray->origin, '+', \
		v3_calc2(ray->direction, '*', (t_vec3){t, t, t}));
		best_hit->normal = v3_calc_normalize(\
		v3_calc2(best_hit->point, '-', obj->coords));
	}
}

void	intersect_plane(t_ray *ray, t_obj *obj, t_hit *best_hit)
{
	double	a;
	double	b;
	double	t;

	b = v3_calc2_dotprod(ray->direction, obj->normal);
	if (fabs(b) < 0.0001)
		return ;
	a = v3_calc2_dotprod(v3_calc2(obj->coords, '-', ray->origin), obj->normal);
	t = a / b;
	if (t <= 0.0001)
		return ;
	if (t < best_hit->dist)
	{
		best_hit->dist = t;
		best_hit->obj = obj;
		best_hit->point = v3_calc2(ray->origin, '+', \
		v3_calc2(ray->direction, '*', (t_vec3){t, t, t}));
		if (b <= 0.0001)
			best_hit->normal = \
			v3_calc2(obj->normal, '*', (t_vec3){-1.0, -1.0, -1.0});
		else
			best_hit->normal = obj->normal;
	}
}
