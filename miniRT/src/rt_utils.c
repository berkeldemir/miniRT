/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:33:14 by beldemir          #+#    #+#             */
/*   Updated: 2025/12/09 14:33:24 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini.h"

int	rt_color(t_color *ptr, char *color)
{
	char	**rgb;

	rgb = ft_split(color, ',');
	if (!rgb)
		return (FAIL);
	if (!rgb[0] || !rgb[1] || !rgb[2])
		return (free_split(rgb), FAIL);
	if (rgb[3] != NULL)
		return (free_split(rgb), FAIL);
	if (rt_atoi(rgb[2], 0, 255, &ptr->b) == FAIL || \
		rt_atoi(rgb[1], 0, 255, &ptr->g) == FAIL || \
		rt_atoi(rgb[0], 0, 255, &ptr->r) == FAIL)
		return (free_split(rgb), FAIL);
	free_split(rgb);
	return (SUCCESS);
}

int	rt_coords(t_vec3 *ptr, char *coords, t_bool limit_one)
{
	char	**xyz;
	double	limit;

	xyz = ft_split(coords, ',');
	if (!xyz)
		return (FAIL);
	if (xyz[3] != NULL)
		return (free_split(xyz), FAIL);
	limit = 999999.0;
	if (limit_one == TRUE)
		limit = 1.0;
	if (rt_atod(xyz[0], -limit, limit, &ptr->x) == FAIL || \
		rt_atod(xyz[1], -limit, limit, &ptr->y) == FAIL || \
		rt_atod(xyz[2], -limit, limit, &ptr->z) == FAIL)
		return (free_split(xyz), FAIL);
	free_split(xyz);
	return (SUCCESS);
}

t_vec3	v3_new(double x, double y, double z)
{
	t_vec3	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}
