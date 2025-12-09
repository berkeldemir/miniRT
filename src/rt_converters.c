/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_converters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:30:56 by beldemir          #+#    #+#             */
/*   Updated: 2025/12/09 14:30:57 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini.h"

static double	ft_atod(const char *str)
{
	double	result;
	double	frac;
	int		sign;
	int		i;

	result = 0.0;
	frac = 0.1;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (ft_isdigit(str[i]))
		result = result * 10.0 + (str[i++] - '0');
	if (str[i] == '.')
		i++;
	while (ft_isdigit(str[i]))
	{
		result += (str[i++] - '0') * frac;
		frac *= 0.1;
	}
	return (result * sign);
}

static int	is_valid_double(const char *s)
{
	int	i;
	int	dot;

	i = 0;
	dot = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!ft_isdigit(s[i]) && s[i] != '.')
		return (FAIL);
	while (s[i])
	{
		if (s[i] == '.')
		{
			if (dot)
				return (FAIL);
			dot = 1;
		}
		else if (!ft_isdigit(s[i]))
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

int	rt_atod(char *str, double min, double max, void *put)
{
	double	value;
	char	*s;

	if (!str)
		return (FAIL);
	s = str;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (is_valid_double(s) == FAIL)
		return (FAIL);
	value = ft_atod(s);
	if (value < min || value > max)
		return (FAIL);
	*(double *)put = value;
	return (SUCCESS);
}

int	rt_atoi(char *str, int min, int max, void *put)
{
	int		i;
	int		value;
	char	*s;

	if (!str)
		return (FAIL);
	s = str;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '-' || *s == '+')
		s++;
	if (!ft_isdigit(*s))
		return (FAIL);
	i = 0;
	while (s[i] && ft_isdigit(s[i]))
		i++;
	if (s[i] != '\0')
		return (FAIL);
	value = ft_atoi(str);
	if (value < min || value > max)
		return (FAIL);
	*(int *)put = value;
	return (SUCCESS);
}
