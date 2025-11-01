#include "../inc/mini.h"

static void	v3_calc2_divider(t_vec3 a, t_vec3 b, t_vec3 *new)
{
	new->x = 0.0;
	new->y = 0.0;
	new->z = 0.0;
	if (a.x != 0.0 && b.x != 0.0)
		new->x = a.x / b.x;
	if (a.y != 0.0 && b.y != 0.0)
		new->y = a.y / b.y;
	if (a.z != 0.0 && b.z != 0.0)
		new->z = a.z / b.z;
	return ;
}

t_vec3	v3_calc2(t_vec3 a, char operation, t_vec3 b)
{
	t_vec3	new;

	if (operation == '+')
	{
		new.x = a.x + b.x;
		new.y = a.y + b.y;
		new.z = a.z + b.z;
	}
	else if (operation == '-')
	{
		new.x = a.x - b.x;
		new.y = a.y - b.y;
		new.z = a.z - b.z;
	}
	else if (operation == '*')
	{
		new.x = a.x * b.x;
		new.y = a.y * b.y;
		new.z = a.z * b.z;
	}
	else if (operation == '/')
		v3_calc2_divider(a, b, &new);
	return (new);
}

double	v3_calc2_dotprod(t_vec3 a, t_vec3 b)
{
	double	res;

	res = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	return (res);
}

t_vec3	v3_calc_normalize(t_vec3 a)
{
	double	len;
	t_vec3	new;

	new.x = 0.0;
	new.y = 0.0;
	new.z = 0.0;
	len = sqrt(v3_calc2_dotprod(a, a));
	if (len == 0)
		return (new);
	new.x = a.x / len;
	new.y = a.y / len;
	new.z = a.z / len;
	return (new);
}

t_vec3	v3_calc2_crossprod(t_vec3 a, t_vec3 b)
{
	t_vec3	new;

	new = v3_new(0.0, 0.0, 0.0);
	new.x = (a.y * b.z) - (a.z * b.y);
	new.y = (a.z * b.x) - (a.x * b.z);
	new.z = (a.x * b.y) - (a.y * b.x);
	return (new);
}
