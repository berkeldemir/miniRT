#include "../inc/mini.h"

static int	camera_moves(int key)
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

static int	object_moves(int key)
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

static int	keyboard_ctrls(int key, void *null)
{
	(void)null;
	if (key == XK_Escape || key == XK_Q || key == XK_q)
		quit(MSG_OK, SUCCESS);
	else if (key == XK_R || key == XK_r)
		(ft_lstclear(&mini()->objs, free), parser());
	else if (key == XK_C || key == XK_c)
		state(SET, NULL);
	else if (state(GET, NULL) == NULL)
	{
		if (camera_moves(key) == FAIL)
			return (FAIL);
	}
	else
	{
		if (object_moves(key) == FAIL)
			return (FAIL);
	}
	render();
	return (SUCCESS);
}

static int	mouse_ctrls(int key, int x, int y, void *null)
{
	t_ray	ray;
	t_hit	best_hit;

	(void)null;
	if (key == 1)
	{
		ray = generate_ray_from_pixel(x, y);
		best_hit = get_hit_record(&ray);
		if (best_hit.obj == NULL)
			state(SET, NULL);
		else
			state(SET, best_hit.obj);
		if (best_hit.obj == NULL)
			printf("LEFT-CLICK! BEST HIT ON SPACE\n");
		else
			printf("LEFT-CLICK! BEST HIT TYPE: %c\n", best_hit.obj->type);
	}
	return (SUCCESS);
}

static int	destroy_notify(void *null)
{
	(void)null;
	quit(MSG_OK, SUCCESS);
	return (SUCCESS);
}

int	start_hooks(void)
{
	mlx_hook(mini()->mlx.win, KeyPress, KeyPressMask, keyboard_ctrls, NULL);
	mlx_hook(mini()->mlx.win, ButtonPress, ButtonPressMask, mouse_ctrls, NULL);
	mlx_hook(mini()->mlx.win, DestroyNotify, 0, destroy_notify, NULL);
	return (SUCCESS);
}
