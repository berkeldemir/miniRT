#include "../inc/mini.h"

static int	keyboard_ctrls(int key, void *null)
{
	(void)null;
	if (key == XK_Escape || key == XK_Q || key == XK_q)
		quit(MSG_OK, SUCCESS);
	else if (key == XK_Up || key == XK_Down \
	|| key == XK_Left || key == XK_Right)
		move_camera(key);
	else if (key == XK_u || key == XK_U \
	|| key == XK_j || key == XK_J)
		move_backandforth(key);
	else if (key == XK_W || key == XK_w \
	|| key == XK_A || key == XK_a \
	|| key == XK_S || key == XK_s \
	|| key == XK_D || key == XK_d)
		move_rotate(key);
	else if (key == XK_R || key == XK_r)
		parser();
	else
		return (FAIL);
	render();
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
	mlx_hook(mini()->mlx.win, DestroyNotify, 0, destroy_notify, NULL);
	return (SUCCESS);
}
