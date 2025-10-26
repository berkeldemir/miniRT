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
	mini()->a.isset = FALSE;
	mini()->c.isset = FALSE;
	mini()->l.isset = FALSE;
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
	parser();

	t_list *lst = mini()->objs;
	int		i = 0;
	while (lst)
	{
		t_obj	*obj = ((t_obj *)lst->content);
		printf("OBJECT %i\n", i);
		printf("Type     : %c\n", obj->type);
		printf("Coords   : %f\t%f\t%f\n", obj->coords.x, obj->coords.y, obj->coords.z);
		printf("Normals  : %f\t%f\t%f\n", obj->normals.x, obj->normals.y, obj->normals.z);
		printf("Diameter : %f\n", obj->diameter);
		printf("Height   : %f\n", obj->height);
		printf("Color    : %d\n", obj->color.value);
		printf("\n");
		lst = lst->next;
		i++;
	}
	mlx_loop(mini()->mlx.mlx);
}
