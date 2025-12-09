/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:52:46 by beldemir          #+#    #+#             */
/*   Updated: 2025/12/09 15:51:41 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini.h"

static int	render_hook(void *null)
{
	int64_t	curr;

	(void)null;
	curr = get_time();
	if (curr - mini()->last_refresh > RERENDER_MS && \
	mini()->render_res == LOW_RES)
	{
		mini()->render_res = HIGH_RES;
		render();
		put_img_to_win();
	}
	return (SUCCESS);
}

static int	keyboard_ctrls(int key, void *null)
{
	(void)null;
	if (key == XK_Escape || key == XK_Q || key == XK_q)
		quit(MSG_OK, SUCCESS);
	else if (key == XK_R || key == XK_r)
		(ft_lstclear(&mini()->objs, free), parser());
	else if ((key == XK_X || key == XK_x) && mini()->shadows == ON)
		mini()->shadows = OFF;
	else if ((key == XK_X || key == XK_x) && mini()->shadows == OFF)
		mini()->shadows = ON;
	else if (key == XK_C || key == XK_c)
		return (state(SET, NULL), SUCCESS);
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
	mini()->render_res = LOW_RES;
	mini()->last_refresh = get_time();
	return (render(), put_img_to_win(), SUCCESS);
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
	mlx_loop_hook(mini()->mlx.mlx, &render_hook, NULL);
	return (SUCCESS);
}
