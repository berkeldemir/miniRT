/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbayram <hbayram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 14:53:14 by hbayram           #+#    #+#             */
/*   Updated: 2025/10/26 16:01:13 by hbayram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini.h"

int	parse_input(char *line)
{
	char **tokens;

	if (!line || !*line)
		return (0);
	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0])
	{
		// handle error
		return (0);
	}
	if (ft_strncmp(tokens[0], "A", 1) == 0)
		parse_ambient(tokens);
	else if (ft_strncmp(tokens[0], "C", 1) == 0)
		parse_camera(tokens);
	else if (ft_strncmp(tokens[0], "L", 1) == 0)
		parse_light(tokens);
	else if (ft_strncmp(tokens[0], "sp", 2) == 0)
		parse_sphere(tokens);
	else if (ft_strncmp(tokens[0], "pl", 2) == 0)
		parse_plane(tokens);
	else if (ft_strncmp(tokens[0], "cy", 2) == 0)
		parse_cylinder(tokens);
	else
		; // handle unknown
	free_split(tokens);
	return (0);
}
