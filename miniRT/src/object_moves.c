/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:23:06 by beldemir          #+#    #+#             */
/*   Updated: 2025/12/09 14:24:13 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini.h"

static t_vec3	rotate_util(t_vec3	vector, double angle)
{
	t_vec3	new;
	t_vec3	cos_vector;
	t_vec3	sin_vector;
	t_vec3	scalar_vector;
	t_obj	*obj;

	obj = state(GET, NULL);
	vector = v3_calc_normalize(vector);
	cos_vector = (t_vec3){cos(angle), cos(angle), cos(angle)};
	sin_vector = (t_vec3){sin(angle), sin(angle), sin(angle)};
	scalar_vector = (t_vec3){\
		v3_calc2_dotprod(obj->normal, vector) * (1.0 - cos(angle)),
		v3_calc2_dotprod(obj->normal, vector) * (1.0 - cos(angle)),
		v3_calc2_dotprod(obj->normal, vector) * (1.0 - cos(angle)),
	};
	new = v3_calc2(obj->normal, '*', cos_vector);
	new = v3_calc2(new, '+', \
		v3_calc2(v3_calc2_cross(obj->normal, vector), '*', sin_vector));
	new = v3_calc2(new, '+', \
		v3_calc2(obj->normal, '*', scalar_vector));
	return (v3_calc_normalize(new));
}

static void	rotate_object(int key)
{
	t_obj	*obj;

	obj = state(GET, NULL);
	if (obj->type == SPHERE)
		return ;
	if (key == XK_Up)
		obj->normal = rotate_util(mini()->c.up, '+');
	if (key == XK_Down)
		obj->normal = rotate_util(mini()->c.up, '-');
	if (key == XK_Right)
		obj->normal = rotate_util(mini()->c.right, '+');
	if (key == XK_Left)
		obj->normal = rotate_util(mini()->c.right, '-');
}

static void	move_util(t_vec3 vector, char mp)
{
	t_obj	*obj;
	int		sign;

	sign = 1;
	if (mp == '-')
		sign = -1;
	obj = state(GET, NULL);
	obj->coords.x = obj->coords.x + (vector.x * sign * MOVE_SPEED);
	obj->coords.y = obj->coords.y + (vector.y * sign * MOVE_SPEED);
	obj->coords.z = obj->coords.z + (vector.z * sign * MOVE_SPEED);
}

static void	move_object(int key)
{
	if (key == XK_W || key == XK_w)
		move_util(mini()->c.normal, '+');
	if (key == XK_A || key == XK_a)
		move_util(mini()->c.right, '-');
	if (key == XK_S || key == XK_s)
		move_util(mini()->c.normal, '-');
	if (key == XK_D || key == XK_d)
		move_util(mini()->c.right, '+');
	if (key == XK_space)
		move_util(mini()->c.up, '+');
	if (key == XK_Shift_L || key == XK_Shift_R)
		move_util(mini()->c.up, '-');
}

int	object_moves(int key)
{
	t_obj	*obj;

	obj = state(GET, NULL);
	if (key == XK_W || key == XK_w \
	|| key == XK_A || key == XK_a \
	|| key == XK_S || key == XK_s \
	|| key == XK_D || key == XK_d || key == XK_space \
	|| key == XK_Shift_L || key == XK_Shift_R)
		move_object(key);
	else if (key == XK_Up || key == XK_Left || \
	key == XK_Down || key == XK_Right)
		rotate_object(key);
	else if ((key == XK_U || key == XK_u) && (obj->diameter != -1))
		state(GET, NULL)->diameter += RATIO;
	else if ((key == XK_J || key == XK_j) && (obj->diameter != -1) && \
	(obj->diameter - RATIO >= 0))
		state(GET, NULL)->diameter -= RATIO;
	else if ((key == XK_O || key == XK_o) && (obj->height != -1))
		state(GET, NULL)->height += RATIO;
	else if ((key == XK_L || key == XK_l) && (obj->height != -1) && \
	(obj->height - RATIO >= 0))
		state(GET, NULL)->height -= RATIO;
	else
		return (FAIL);
	return (SUCCESS);
}
