/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:58:57 by beldemir          #+#    #+#             */
/*   Updated: 2025/12/09 14:15:19 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini.h"

// ???
static t_vec3	rotate_yaw(char mp)
{
	double	angle;
	t_vec3	new_dir;

	angle = ROTATE_SPEED;
	if (mp == '-')
		angle *= -1;
	new_dir.x = mini()->c.normal.x * cos(angle) + \
	mini()->c.normal.z * sin(angle);
	new_dir.z = -mini()->c.normal.x * sin(angle) + \
	mini()->c.normal.z * cos(angle);
	new_dir.y = mini()->c.normal.y;
	return (v3_calc_normalize(new_dir));
}

// ???
static t_vec3	rotate_pitch(char mp)
{
	double	angle;
	t_vec3	term1;
	t_vec3	term2;
	t_vec3	new_dir;

	angle = ROTATE_SPEED;
	if (mp == '-')
		angle *= -1;
	term1 = v3_calc2(mini()->c.normal, '*', \
	(t_vec3){cos(angle), cos(angle), cos(angle)});
	term2 = v3_calc2(mini()->c.up, '*', \
	(t_vec3){sin(angle), sin(angle), sin(angle)});
	new_dir = v3_calc2(term1, '+', term2);
	return (v3_calc_normalize(new_dir));
}

static void	rotate_camera(int key)
{
	if (key == XK_Up)
		mini()->c.normal = rotate_pitch('+');
	if (key == XK_Left)
		mini()->c.normal = rotate_yaw('-');
	if (key == XK_Down)
		mini()->c.normal = rotate_pitch('-');
	if (key == XK_Right)
		mini()->c.normal = rotate_yaw('+');
}

static void	move_camera(int key)
{
	t_vec3	speed_vec;
	t_vec3	step_up;
	t_vec3	step_right;
	t_vec3	move_step;
	t_mini	*m;

	m = mini();
	speed_vec = (t_vec3){MOVE_SPEED, MOVE_SPEED, MOVE_SPEED};
	move_step = v3_calc2(mini()->c.normal, '*', \
	(t_vec3){MOVE_SPEED, MOVE_SPEED, MOVE_SPEED});
	step_up = v3_calc2(mini()->c.up, '*', speed_vec);
	step_right = v3_calc2(mini()->c.right, '*', speed_vec);
	if (key == XK_W || key == XK_w)
		m->c.coords = v3_calc2(m->c.coords, '+', move_step);
	if (key == XK_A || key == XK_a)
		m->c.coords = v3_calc2(m->c.coords, '-', step_right);
	if (key == XK_S || key == XK_s)
		m->c.coords = v3_calc2(m->c.coords, '-', move_step);
	if (key == XK_D || key == XK_d)
		m->c.coords = v3_calc2(m->c.coords, '+', step_right);
	if (key == XK_space)
		m->c.coords = v3_calc2(m->c.coords, '+', step_up);
	else if (key == XK_Shift_L || key == XK_Shift_R)
		m->c.coords = v3_calc2(m->c.coords, '-', step_up);
}

int	camera_moves(int key)
{
	if (key == XK_W || key == XK_w \
	|| key == XK_A || key == XK_a \
	|| key == XK_S || key == XK_s \
	|| key == XK_D || key == XK_d \
	|| key == XK_Shift_L || key == XK_Shift_R \
	|| key == XK_space)
		move_camera(key);
	else if (key == XK_Up || key == XK_Left || \
	key == XK_Down || key == XK_Right)
		rotate_camera(key);
	else
		return (FAIL);
	return (SUCCESS);
}
