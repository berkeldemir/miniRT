#include "../inc/mini.h"

uint64_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((uint64_t)((tv.tv_sec * 1000) + (tv.tv_usec / 1000)));
}

t_mini	*mini(void)
{
	static t_mini	*info = NULL;

	if (info == NULL)
	{
		info = ft_calloc(sizeof(t_mini), 1);
		if (!info)
			return (NULL);
	}
	return (info);
}

t_obj	*state(char getset, t_obj *obj)
{
	static t_obj	*current_state = NULL;

	if (getset == GET)
		return (current_state);
	else if (getset == SET)
	{
		current_state = obj;
		if (obj == NULL)
			printf("STATE UPDATED: NULL\n");
		else
			printf("STATE UPDATED: %c\n", obj->type);
	}
	return (NULL);
}

int	arg_control(int ac, char **av)
{
	int	i;

	if (ac != 2)
		return (FAIL);
	i = 0;
	while (av[1][i])
		i++;
	if (i < 4 || \
		av[1][i - 3] != '.' || \
		av[1][i - 2] != 'r' || \
		av[1][i - 1] != 't')
		return (FAIL);
	mini()->file_name = av[1];
	return (SUCCESS);
}

void	quit(char *msg, int retval)
{
	if (mini()->mlx.img)
		mlx_destroy_image(mini()->mlx.mlx, mini()->mlx.img);
	if (mini()->mlx.win)
		mlx_destroy_window(mini()->mlx.mlx, mini()->mlx.win);
	if (mini()->mlx.mlx)
		mlx_destroy_display(mini()->mlx.mlx);
	free(mini()->mlx.mlx);
	mini()->mlx.mlx = NULL;
	mini()->mlx.win = NULL;
	mini()->mlx.img = NULL;
	ft_lstclear(&mini()->objs, free);
	free(mini());
	if (retval != 0)
		printf("%s%s %s %s\n", ERR, COLOR_RED, msg, COLOR_RESET);
	exit(retval);
}
