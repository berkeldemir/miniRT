/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbayram <hbayram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 14:53:14 by hbayram           #+#    #+#             */
/*   Updated: 2025/10/26 16:01:13 by hbayram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini.h"

void	free_split(char **split)
{
	int i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}


static int	parse_input(char *line)
{
	char **tokens;

	if (!line || !*line)
		return (0);
	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0])
		return (FAIL);
	else if (ft_strncmp(tokens[0], "#", 1) == 0)
		return (free(tokens), printf("COMMENTLINE\n"), SUCCESS);
	else if (ft_strncmp(tokens[0], "A", 1) == 0)
		return (parse_ambient(&tokens));
	else if (ft_strncmp(tokens[0], "C", 1) == 0)
		return (parse_camera(&tokens));
	else if (ft_strncmp(tokens[0], "L", 1) == 0)
		return (parse_light(&tokens));
	else if (ft_strncmp(tokens[0], "sp", 2) == 0)
		return (parse_sphere(&tokens));
	else if (ft_strncmp(tokens[0], "pl", 2) == 0)
		return (parse_plane(&tokens));
	else if (ft_strncmp(tokens[0], "cy", 2) == 0)
		return (parse_cylinder(&tokens));
	else
		return (free(tokens), FAIL);
	return (SUCCESS);
}

static char	*clear_line(char *line)
{
	char	*new_line;
	int		i;

	i = 0;
	new_line = ft_strdup(line);
	free(line);
	while (new_line[i])
	{
		if (new_line[i] == '\n' || new_line[i] == '\t')
			new_line[i] = ' ';
		i++;
	}
	line = ft_strtrim(new_line, " ");
	free(new_line);
	return (line);
}

int	parser(void)
{
	int		fd;
	char	*line;

	fd = open(mini()->file_name, O_RDONLY);
	if (fd < 0)
		quit(ERR_OPENFAIL, FAIL);
	mini()->a.isset = FALSE;
	mini()->c.isset = FALSE;
	mini()->l.isset = FALSE;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		line = clear_line(line);
		if (parse_input(line) == FAIL)
			return (free(line), FAIL);
		free(line);
	}
	close(fd);
	if (mini()->a.isset == FALSE || \
		mini()->c.isset == FALSE || \
		mini()->l.isset == FALSE)
		return (FAIL);
	return (SUCCESS);
}
