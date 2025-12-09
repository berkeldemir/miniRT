/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 14:58:06 by hbayram           #+#    #+#             */
/*   Updated: 2025/12/09 19:55:46 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini.h"

int	parse_ambient(char ***tokens)
{
	if (mini()->a.isset == TRUE)
		return (FAIL);
	if (rt_atod(tokens[0][1], 0.0, 1.0, &mini()->a.ratio) == FAIL)
		return (FAIL);
	if (rt_color(&mini()->a.color, tokens[0][2]) == FAIL)
		return (FAIL);
	mini()->a.isset = TRUE;
	free_split(*tokens);
	return (SUCCESS);
}

int	parse_camera(char ***tokens)
{
	if (mini()->c.isset == TRUE)
		return (FAIL);
	if (rt_coords(&mini()->c.coords, tokens[0][1], FALSE) == FAIL)
		return (FAIL);
	if (rt_coords(&mini()->c.normal, tokens[0][2], TRUE) == FAIL)
		return (FAIL);
	if (rt_atoi(tokens[0][3], 0, 180, &mini()->c.h_degree) == FAIL)
		return (FAIL);
	mini()->c.isset = TRUE;
	free_split(*tokens);
	return (SUCCESS);
}

int	parse_light(char ***tokens)
{
	if (mini()->l.isset == TRUE)
		return (FAIL);
	if (rt_coords(&mini()->l.coords, tokens[0][1], FALSE) == FAIL)
		return (FAIL);
	if (rt_atod(tokens[0][2], 0.0, 1.0, &mini()->l.brightness) == FAIL)
		return (FAIL);
	if (tokens[0][3])
	{
		if (rt_color(&mini()->l.color, tokens[0][3]) == FAIL)
			return (FAIL);
	}
	else
	{
		if (rt_color(&mini()->l.color, "255,255,255") == FAIL)
			return (FAIL);
	}
	mini()->l.isset = TRUE;
	free_split(*tokens);
	return (SUCCESS);
}
