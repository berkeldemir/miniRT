#include "../inc/mini.h"

// ???
static t_vec3   rotate_yaw(char mp)
{
	double	angle;
	t_vec3	new_dir;

	if (mp == '+')
		angle = 0.1;
	else
		angle = -0.1;
	new_dir.x = mini()->c.normal.x * cos(angle) + mini()->c.normal.z * sin(angle);
	new_dir.z = -mini()->c.normal.x * sin(angle) + mini()->c.normal.z * cos(angle);
	new_dir.y = mini()->c.normal.y;

	return (v3_calc_normalize(new_dir));
}

// ???
static t_vec3   rotate_pitch(char mp)
{
	double	angle;
    t_vec3  term1;
    t_vec3  term2;
    t_vec3  new_dir;

	if (mp == '+')
		angle = 0.1;
	else
		angle = -0.1;
    term1 = v3_calc2(mini()->c.normal, '*', (t_vec3){cos(angle), cos(angle), cos(angle)});
    term2 = v3_calc2(mini()->c.up, '*', (t_vec3){sin(angle), sin(angle), sin(angle)});
    new_dir = v3_calc2(term1, '+', term2);

    return (v3_calc_normalize(new_dir));
}

void	move_rotate(int key)
{
	if (key == XK_W || key == XK_w)
		mini()->c.normal = rotate_pitch('+');
	if (key == XK_A || key == XK_a)
		mini()->c.normal = rotate_yaw('-');
	if (key == XK_S || key == XK_s)
		mini()->c.normal = rotate_pitch('-');
	if (key == XK_D || key == XK_d)
		mini()->c.normal = rotate_yaw('+');
}

void move_camera(int key)
{
	double	move_speed;
	t_vec3	speed_vec;
	t_vec3	step;

	move_speed = 1;
	speed_vec = (t_vec3){move_speed, move_speed, move_speed};
	if (key == XK_Up || key == XK_Down)
	{
		step = v3_calc2(mini()->c.up, '*', speed_vec);
		if (key == XK_Up)
			mini()->c.coords = v3_calc2(mini()->c.coords, '+', step);
		if (key == XK_Down)
			mini()->c.coords = v3_calc2(mini()->c.coords, '-', step);
	}
	else
	{
		step = v3_calc2(mini()->c.right, '*', speed_vec);
		if (key == XK_Right)
			mini()->c.coords = v3_calc2(mini()->c.coords, '+', step);
		if (key == XK_Left)
			mini()->c.coords = v3_calc2(mini()->c.coords, '-', step);
	}
}

void move_backandforth(int key)
{
	double	move_speed;
	t_vec3	move_step;

	move_speed = 1;
	move_step = v3_calc2(mini()->c.normal, '*', \
	(t_vec3){move_speed, move_speed, move_speed});
	if (key == XK_u || key == XK_U)
		mini()->c.coords = v3_calc2(mini()->c.coords, '+', move_step);
	else if (key == XK_j || key == XK_J)
		mini()->c.coords = v3_calc2(mini()->c.coords, '-', move_step);
}
