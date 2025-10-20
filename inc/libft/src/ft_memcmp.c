/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:50:04 by beldemir          #+#    #+#             */
/*   Updated: 2025/02/21 21:57:51 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*ptr1;
	char	*ptr2;
	size_t	i;

	ptr1 = (char *)s1;
	ptr2 = (char *)s2;
	i = 0;
	while (i < n)
	{
		if (ptr1[i] != ptr2[i])
			return ((unsigned char)ptr1[i] - (unsigned char)ptr2[i]);
		i++;
	}
	return (0);
}
