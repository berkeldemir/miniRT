/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:18:08 by beldemir          #+#    #+#             */
/*   Updated: 2025/02/21 21:58:39 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	index;
	char	*new;

	i = ft_strlen((char *)s1);
	j = ft_strlen((char *)s2);
	index = 0;
	new = (char *)malloc(sizeof(char) * (i + j + 1));
	if (!new)
		return (NULL);
	while (index < i)
	{
		new[index] = s1[index];
		index++;
	}
	while (index < i + j)
	{
		new[index] = s2[index - i];
		index++;
	}
	new[index] = '\0';
	return (new);
}
