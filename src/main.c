#include "../inc/mini.h"

int	initializer(void)
{
	t_mini	*m;

	m = mini();
	m->mlx.mlx = mlx_init();
	m->mlx.win = mlx_new_window(m->mlx.mlx, W, H, TITLE);
	m->mlx.img = mlx_new_image(m->mlx.mlx, W, H);
	m->mlx.ptr = mlx_get_data_addr(m->mlx.img, &m->mlx.bpp, &m->mlx.sizeline,
			&m->mlx.endian);
	if (!m->mlx.mlx || !m->mlx.win || !m->mlx.img || !m->mlx.ptr)
		return (FAIL);
	if (start_hooks() == FAIL)
		return (FAIL);
	printf("%s\n", mini()->file_name);
	return (SUCCESS);
}

int	main(int ac, char **av)
{
	if (!mini())
		quit(ERR_CALLOCFAIL, FAIL);
	if (arg_control(ac, av) == FAIL)
		quit(ERR_WRONG_ARGS, FAIL);
	if (initializer() == FAIL)
		quit(ERR_INITIALIZE, FAIL);
	mlx_loop(mini()->mlx.mlx);
}
