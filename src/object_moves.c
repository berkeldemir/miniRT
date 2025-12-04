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
	v3_calc2(obj->normal, '*', scalar_vector)
	);
	return (v3_calc_normalize(new));
}

void	rotate_object(int key)
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

void	move_object(int key)
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
