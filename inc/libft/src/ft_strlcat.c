/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:14:27 by beldemir          #+#    #+#             */
/*   Updated: 2025/02/21 21:58:46 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	j;
	size_t	dstlen;
	size_t	srclen;

	j = 0;
	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (dstsize <= dstlen)
		return (dstsize + srclen);
	while (src[j] != '\0' && (dstlen + j) < (dstsize - 1))
	{
		dst[dstlen + j] = src[j];
		j++;
	}
	if ((dstlen + j) < dstsize)
		dst[dstlen + j] = '\0';
	return (dstlen + srclen);
}
