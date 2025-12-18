/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:15:43 by beldemir          #+#    #+#             */
/*   Updated: 2025/12/09 14:18:03 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini.h"

static int	check_height(t_obj *obj, t_ray *ray, double t, double *m)
{
	t_vec3	p;

	p = v3_calc2(ray->origin, '+', v3_calc2(ray->direction, '*', (t_vec3){t, t,
				t}));
	*m = v3_calc2_dotprod(v3_calc2(p, '-', obj->coords), obj->normal);
	if (*m >= -(obj->height / 2.0) && *m <= (obj->height / 2.0))
		return (SUCCESS);
	return (FAIL);
}

static void	check_cap(t_ray *ray, t_obj *obj, t_hit *best_hit,
		t_vec3 cap_center, t_vec3 cap_normal)
{
	double	denom;
	double	t;
	t_vec3	p;
	t_vec3	v;
	double	r_sq;

	denom = v3_calc2_dotprod(ray->direction, cap_normal);
	if (fabs(denom) < 1e-6)
		return ;
	t = v3_calc2_dotprod(v3_calc2(cap_center, '-', ray->origin), cap_normal)
		/ denom;
	if (t < 0.0001 || t >= best_hit->dist)
		return ;
	p = v3_calc2(ray->origin, '+', v3_calc2(ray->direction, '*', (t_vec3){t, t,
				t}));
	v = v3_calc2(p, '-', cap_center);
	r_sq = (obj->diameter / 2.0) * (obj->diameter / 2.0);
	if (v3_calc2_dotprod(v, v) <= r_sq)
	{
		best_hit->dist = t;
		best_hit->obj = obj;
		best_hit->point = p;
		best_hit->normal = cap_normal;
	}
}

static void update_cylinder_hit(t_ray *ray, t_obj *obj, t_hit *best_hit, double m)
{
    t_vec3	axis_component;
	t_vec3	relative_pos;
    
    axis_component = v3_calc2(obj->normal, '*', (t_vec3){m, m, m});
	relative_pos = v3_calc2(best_hit->point, '-', obj->coords);
	best_hit->normal = v3_calc_normalize(v3_calc2(relative_pos, '-', axis_component));
	if (v3_calc2_dotprod(ray->direction, best_hit->normal) > 0)
		best_hit->normal = v3_calc2(best_hit->normal, '*', (t_vec3){-1, -1, -1});
}

static void	handle_cylinder_hit(t_ray *ray, t_obj *obj, t_hit *best_hit,
		t_quad q)
{
	double	m;
	double	t;

	q.t1 = (-q.b - sqrt(q.delta)) / (2.0 * q.a);
	q.t2 = (-q.b + sqrt(q.delta)) / (2.0 * q.a);
	t = -1.0;
	if (q.t1 > 0.0001 && check_height(obj, ray, q.t1, &m) == SUCCESS)
		t = q.t1;
	else if (q.t2 > 0.0001 && check_height(obj, ray, q.t2, &m) == SUCCESS)
		t = q.t2;
	if (t > 0.0001 && t < best_hit->dist)
	{
		best_hit->dist = t;
		best_hit->obj = obj;
		best_hit->point = v3_calc2(ray->origin, '+',
				v3_calc2(ray->direction, '*', (t_vec3){t, t, t}));
        update_cylinder_hit(ray, obj, best_hit, m);
	}
}

void	intersect_cylinder(t_ray *ray, t_obj *obj, t_hit *best_hit)
{
	t_vec3	oc;
	t_vec3	cross_d_n;
	t_vec3	cross_oc_n;
	t_quad	q;
	t_vec3	half_h_vec;

	oc = v3_calc2(ray->origin, '-', obj->coords);
	cross_d_n = v3_calc2_cross(ray->direction, obj->normal);
	cross_oc_n = v3_calc2_cross(oc, obj->normal);
	q.a = v3_calc2_dotprod(cross_d_n, cross_d_n);
	q.b = 2.0 * v3_calc2_dotprod(cross_d_n, cross_oc_n);
	q.c = v3_calc2_dotprod(cross_oc_n, cross_oc_n) - ((obj->diameter / 2.0)
			* (obj->diameter / 2.0));
	q.delta = (q.b * q.b) - (4 * q.a * q.c);
	if (q.delta >= 0)
	{
		handle_cylinder_hit(ray, obj, best_hit, q);
	}
	half_h_vec = v3_calc2(obj->normal, '*', (t_vec3){obj->height / 2.0,
			obj->height / 2.0, obj->height / 2.0});
	check_cap(ray, obj, best_hit, v3_calc2(obj->coords, '+', half_h_vec),
		obj->normal);
	check_cap(ray, obj, best_hit, v3_calc2(obj->coords, '-', half_h_vec),
		v3_calc2(obj->normal, '*', (t_vec3){-1, -1, -1}));
}
