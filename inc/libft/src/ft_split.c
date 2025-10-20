/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:39:31 by beldemir          #+#    #+#             */
/*   Updated: 2025/02/21 21:58:22 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static void	*delete(char **s, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(s[i]);
		i++;
	}
	free (s);
	return (NULL);
}

static int	ft_count_words(char const *s, char sep)
{
	int	count;

	count = 0;
	if (sep == '\0')
		return (1);
	while (*s)
	{
		if (*s != sep && (*(s + 1) == sep || *(s + 1) == '\0'))
			count++;
		s++;
	}
	return (count);
}

static char	**ft_split_while(char const *s, char c, char **words)
{
	size_t	word_len;
	int		i;

	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			if (ft_strchr(s, c) == NULL)
				word_len = ft_strlen(s);
			else
				word_len = ft_strchr(s, c) - s;
			words[i] = ft_substr(s, 0, word_len);
			if (!words[i])
				return (delete(words, i));
			i++;
			s += word_len;
		}
	}
	words[i] = NULL;
	return (words);
}

char	**ft_split(char const *s, char c)
{
	char	**words;

	words = (char **)malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (words == NULL)
		return (NULL);
	words = ft_split_while(s, c, words);
	return (words);
}
