/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbayram <hbayram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 14:58:06 by hbayram           #+#    #+#             */
/*   Updated: 2025/10/26 15:31:17 by hbayram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini.h"

int	parse_ambient(char ***tokens)
{
	if (mini()->a_set == TRUE)
		return (FAIL);
	printf("\n--> AMBIENT LIGHT <--\n");
	if (rt_atod(tokens[0][1], 0.0, 1.0, &mini()->a.ratio) == FAIL)
		return (FAIL);
	printf("Ratio: %f\n", mini()->a.ratio);
	if (assign_color(&mini()->a.color, tokens[0][2]) == FAIL)
		return (FAIL);
	printf("Color: %i\n", mini()->a.color.value);
	mini()->a_set = TRUE;
	free_split(*tokens);
	return (SUCCESS);
}

int	parse_camera(char ***tokens)
{
	if (mini()->c_set == TRUE)
		return (FAIL);
	printf("\n--> CAMERA <--\n");
	if (assign_coords(&mini()->c.coords, tokens[0][1], FALSE) == FAIL)
		return (FAIL);
	printf("Coords : %f\t%f\t%f\n", mini()->c.coords.x, mini()->c.coords.y, mini()->c.coords.z);
	if (assign_coords(&mini()->c.normals, tokens[0][2], TRUE) == FAIL)
		return (FAIL);
	printf("Normals: %f\t%f\t%f\n", mini()->c.normals.x, mini()->c.normals.y, mini()->c.normals.z);
	if (rt_atoi(tokens[0][3], 0, 180, &mini()->c.h_degree) == FAIL)
		return (FAIL);
	printf("FOV    : %i\n", mini()->c.h_degree);
	mini()->c_set = TRUE;
	free_split(*tokens);
	return (SUCCESS);
}

int	parse_light(char ***tokens)
{
	if (mini()->l_set == TRUE)
		return (FAIL);
	printf("\n--> LIGHT <--\n");
	if (assign_coords(&mini()->l.coords, tokens[0][1], FALSE) == FAIL)
		return (FAIL);
	printf("Coords: %f\t%f\t%f\n", mini()->l.coords.x, mini()->l.coords.y, mini()->l.coords.z);
	if (rt_atod(tokens[0][2], 0.0, 1.0, &mini()->l.brightness) == FAIL)
		return (FAIL);
	printf("Brig..: %f\n", mini()->l.brightness);
	if (tokens[0][3])
	{
		if (assign_color(&mini()->l.color, tokens[0][3]) == FAIL)
			return (FAIL);
	}
	else
	{
		if (assign_color(&mini()->l.color, "255,255,255") == FAIL)
			return (FAIL);
	}
	printf("Color : %i\n", mini()->l.color.value);
	mini()->l_set = TRUE;
	free_split(*tokens);
	return (SUCCESS);
}
