/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:17:46 by beldemir          #+#    #+#             */
/*   Updated: 2025/02/21 21:58:34 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_striteri(char *str, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	if (!str || !f)
		return ;
	while (str[i] != '\0')
	{
		(f)(i, &str[i]);
		i++;
	}
}
