#include "../inc/mini.h"

t_mini	*mini(void)
{
	static t_mini	*info = NULL;

	if (info == NULL)
	{
		info = ft_calloc(sizeof(t_mini), 1);
		if (!info)
			return (NULL);
	}
	return (info);
}

char	*clear_line(char *line)
{
	char	*new_line;
	int		i;

	i = 0;
	new_line = ft_strdup(line);
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

int	open_file(void)
{
	int		fd;
	int		flag;
	char	*line;

	flag = 0;
	fd = open(mini()->file_name, O_RDONLY);
	if (fd < 0)
		quit(ERR_OPENFAIL, FAIL);
	while (flag != 1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		line = clear_line(line);
		if(parse_input(line))
			flag = 1;
		free(line);
	}
	close(fd);
	return (SUCCESS);
}

int	arg_control(int ac, char **av)
{
	int	i;

	if (ac != 2)
		return (FAIL);
	i = 0;
	while (av[1][i])
		i++;
	if (i < 4 || av[1][i - 3] != '.' || av[1][i - 2] != 'r' || av[1][i
		- 1] != 't')
		return (FAIL);
	mini()->file_name = av[1];
	open_file();
	return (SUCCESS);
}

void	quit(char *msg, int retval)
{
	if (ft_strncmp(msg, ERR_CALLOCFAIL, ft_strlen(msg)) == FALSE)
	{
		if (mini()->mlx.img)
			mlx_destroy_image(mini()->mlx.mlx, mini()->mlx.img);
		if (mini()->mlx.win)
			mlx_destroy_window(mini()->mlx.mlx, mini()->mlx.win);
		if (mini()->mlx.mlx)
			mlx_destroy_display(mini()->mlx.mlx);
		free(mini()->mlx.mlx);
		mini()->mlx.mlx = NULL;
		mini()->mlx.win = NULL;
		mini()->mlx.img = NULL;
		free(mini());
	}
	printf("%s%s%s\n", COLOR_RED, msg, COLOR_RESET);
	exit(retval);
}
