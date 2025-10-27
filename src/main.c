#include "../inc/mini.h"

int	initializer(void)
{
	t_mini	*m;

	m = mini();
	m->mlx.mlx = mlx_init();
	m->mlx.win = mlx_new_window(m->mlx.mlx, W, H, TITLE);
	m->mlx.img = mlx_new_image(m->mlx.mlx, W, H);
	m->mlx.ptr = mlx_get_data_addr(m->mlx.img, &m->mlx.bpp, \
				&m->mlx.sizeline, \
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
		quit(ERR_CALLOC, FAIL);
	if (arg_control(ac, av) == FAIL)
		quit(ERR_ARGS, FAIL);
	if (parser() == FAIL)
		quit(ERR_PARSE, FAIL);
	if (initializer() == FAIL)
		quit(ERR_INITIALIZE, FAIL);
	if (draw() == FAIL)
		quit(ERR_DRAW, FAIL);
	/*
	t_list *lst = mini()->objs;
	int		i = 1;
	while (lst)
	{
		t_obj	*obj = ((t_obj *)lst->content);
		printf("OBJECT %i\n", i);
		printf("Type     : %c\n", obj->type);
		printf("Coords   : %f\t%f\t%f\n", obj->coords.x, obj->coords.y, obj->coords.z);
		printf("normal  : %f\t%f\t%f\n", obj->normal.x, obj->normal.y, obj->normal.z);
		printf("Diameter : %f\n", obj->diameter);
		printf("Height   : %f\n", obj->height);
		printf("Color    : %d\n", obj->color.value);
		printf("\n");
		lst = lst->next;
		i++;
	}*/
	mlx_loop(mini()->mlx.mlx);
}
