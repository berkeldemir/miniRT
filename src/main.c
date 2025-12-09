/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:50:58 by beldemir          #+#    #+#             */
/*   Updated: 2025/12/09 19:51:42 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini.h"

void	put_img_to_win(void)
{
	mlx_clear_window(mini()->mlx.mlx, mini()->mlx.win);
	mlx_put_image_to_window(\
	mini()->mlx.mlx, mini()->mlx.win, mini()->mlx.img, 0, 0);
}

static int	normalize_normals(void)
{
	t_list	*obj;

	obj = mini()->objs;
	mini()->c.normal = v3_calc_normalize(mini()->c.normal);
	while (obj != NULL)
	{
		((t_obj *)obj->content)->normal = \
		v3_calc_normalize(((t_obj *)obj->content)->normal);
		obj = obj->next;
	}
	return (SUCCESS);
}

static int	initializer(void)
{
	t_mini	*m;

	m = mini();
	m->render_res = HIGH_RES;
	m->mlx.mlx = mlx_init();
	m->mlx.win = mlx_new_window(m->mlx.mlx, W, H, TITLE);
	m->mlx.img = mlx_new_image(m->mlx.mlx, W, H);
	m->mlx.ptr = mlx_get_data_addr(m->mlx.img, &m->mlx.bpp, \
				&m->mlx.sizeline, \
				&m->mlx.endian);
	if (!m->mlx.mlx || !m->mlx.win || !m->mlx.img || !m->mlx.ptr)
		return (FAIL);
	normalize_normals();
	m->shadows = ON;
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
	if (render() == FAIL)
		quit(ERR_DRAW, FAIL);
	else
		put_img_to_win();
	mlx_loop(mini()->mlx.mlx);
}
