#include "../inc/mini.h"

static double	solve_quad_find_t(t_quad *q)
{
	q->delta = (q->b * q->b) - (4 * q->a * q->c);
	if (q->delta < 0)
		return (0);
	q->t1 = (-q->b - sqrt(q->delta)) / (2.0 * q->a);
	q->t2 = (-q->b + sqrt(q->delta)) / (2.0 * q->a);
	if (q->t1 > 0.0001 && (q->t1 < q->t2 || q->t2 < 0.0001))
		return(q->t1);
	else if (q->t2 > 0.0001)
		return(q->t2);
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
		// p = O + (d * t)
		best_hit->point = v3_calc2(ray->origin, '+', \
		v3_calc2(ray->direction, '*', (t_vec3){t, t, t}));
		// Kürenin normali = (Çarpma Noktası - Kürenin Merkezi)
		best_hit->normal = v3_calc_normalize( \
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
			v3_calc2(obj->normal, '*', (t_vec3){-1.0,-1.0,-1.0});
		else
			best_hit->normal = obj->normal;
	}
}
// Silindirin eksenine dik vektörlerin çarpımı ****

void	intersect_cylinder(t_ray *ray, t_obj *obj, t_hit *best_hit)
{
	t_vec3	oc;
	t_vec3	ray_x_axis;
	t_vec3	oc_x_axis;
	t_quad	q;
	double	t;
	double	radius;
	double	h;
	t_vec3	hit_point;
	double	projection;
	t_vec3	temp;

	oc = v3_calc2(ray->origin, '-', obj->coords);
	ray_x_axis = v3_calc2_cross(ray->direction, obj->normal);
	oc_x_axis = v3_calc2_cross(oc, obj->normal);
	radius = obj->diameter / 2.0;
	q.a = v3_calc2_dotprod(ray_x_axis, ray_x_axis);
	q.b = 2.0 * v3_calc2_dotprod(ray_x_axis, oc_x_axis);
	q.c = v3_calc2_dotprod(oc_x_axis, oc_x_axis) - (radius * radius);
	t = solve_quad_find_t(&q);
	if (t > 0.0001)
	{
		hit_point = v3_calc2(ray->origin, '+', \
			v3_calc2(ray->direction, '*', (t_vec3){t, t, t}));
		temp = v3_calc2(hit_point, '-', obj->coords);
		projection = v3_calc2_dotprod(temp, obj->normal);
		h = obj->height / 2.0;
		if (projection >= -h && projection <= h && t < best_hit->dist)
		{
			best_hit->dist = t;
			best_hit->obj = obj;
			best_hit->point = hit_point;
			temp = v3_calc2(hit_point, '-', obj->coords);
			temp = v3_calc2(temp, '-', \
				v3_calc2(obj->normal, '*', \
					(t_vec3){projection, projection, projection}));
			best_hit->normal = v3_calc_normalize(temp);
		}
	}
}
