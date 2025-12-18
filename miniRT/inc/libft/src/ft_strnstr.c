/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:51:37 by beldemir          #+#    #+#             */
/*   Updated: 2025/02/21 21:59:07 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t		i;
	size_t		j;
	char		*found;

	if (s2[0] == '\0')
		return ((char *)s1);
	i = 0;
	while (i < len && s1[i] != '\0')
	{
		j = 0;
		if (s1[i] == s2[j])
		{
			found = (char *)&s1[i];
			while (s1[i + j] == s2[j] && (i + j) < len)
				if (s2[++j] == '\0')
					return (found);
		}
		i++;
	}
	return (NULL);
}
