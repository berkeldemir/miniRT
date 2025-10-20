/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:06:09 by beldemir          #+#    #+#             */
/*   Updated: 2025/02/21 21:59:13 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	*lastonefound;

	lastonefound = NULL;
	c = (unsigned char)c;
	while (*s != '\0')
	{
		if (*s == (char)c)
			lastonefound = (unsigned char *)s;
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return ((char *)lastonefound);
}
