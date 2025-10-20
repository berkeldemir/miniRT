#include "../inc/mini.h"

static int keyboard_ctrls(int key, void *null)
{
	(void)null;
	if (key == XK_Escape)
		quit(MSG_OK, 0);
	return (SUCCESS);
}

static int	destroy_notify(void	*null)
{
	(void)null;
	quit(MSG_OK, 0);
	return (SUCCESS);
}

int	start_hooks(void)
{
	mlx_hook(mini()->mlx.win, KeyPress, KeyPressMask, keyboard_ctrls, NULL);
	mlx_hook(mini()->mlx.win, DestroyNotify, 0, destroy_notify, NULL);
	return (SUCCESS);
}
