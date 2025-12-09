/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 20:07:13 by beldemir          #+#    #+#             */
/*   Updated: 2025/12/09 20:23:44 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini.h"

int	destroy_notify(void *null)
{
	(void)null;
	quit(MSG_OK, SUCCESS);
	return (SUCCESS);
}

/*static void	ft_putfloat_fd(int val, int fd)
{
	char	*s;

	
}*/

static void	save_file(void)
{
	char	*file_name;
	char	*time_str;
	int		fd;

	time_str = ft_itoa((int)get_time());
	file_name = ft_strjoin(time_str, ".rt");
	fd = open(file_name, O_CREAT | O_WRONLY);
	ft_putstr_fd("A ", fd);
	printf("File saved: %s\n", file_name);
	free(file_name);
}

int  basic_controls(int key)
{
	if (key == XK_Escape || key == XK_Q || key == XK_q)
		quit(MSG_OK, SUCCESS);
	else if (key == XK_R || key == XK_r)
		(ft_lstclear(&mini()->objs, free), parser());
	else if ((key == XK_X || key == XK_x) && mini()->shadows == ON)
		mini()->shadows = OFF;
	else if ((key == XK_X || key == XK_x) && mini()->shadows == OFF)
		mini()->shadows = ON;
	else if (key == XK_Control_L || key == XK_Control_R)
		mini()->ctrl_hold = TRUE;
	else if ((key == XK_S || key == XK_s) && mini()->ctrl_hold == TRUE)
		save_file();
	else if (key == XK_C || key == XK_c)
		return (state(SET, NULL), TRUE);
	else
		return (FALSE);
	return (TRUE);
}
