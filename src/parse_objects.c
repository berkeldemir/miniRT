/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbayram <hbayram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 14:58:06 by hbayram           #+#    #+#             */
/*   Updated: 2025/10/26 15:31:17 by hbayram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini.h"

int	parse_ambient(char **tokens)
{
    (void)tokens;
    printf("ambient light\n");
    return (0);
}

int	parse_camera(char **tokens)
{
    (void)tokens;
    printf("camera\n");
    return (0);
}

int	parse_light(char **tokens)
{
    (void)tokens;
    printf("light\n");
    return (0);
}

int	parse_sphere(char **tokens)
{
    (void)tokens;
    printf("sphere\n");
    return (0);
}

int	parse_plane(char **tokens)
{
    (void)tokens;
    printf("plane\n");
    return (0);
}

int	parse_cylinder(char **tokens)
{
    (void)tokens;
    printf("cylinder\n");
    return (0);
}
