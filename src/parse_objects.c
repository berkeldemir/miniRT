#include "../inc/mini.h"

int	parse_sphere(char ***tokens)
{
	(void)tokens;
	printf("\n--> SPHERE <--\n");
	free_split(*tokens);
	return (SUCCESS);
}

int	parse_plane(char ***tokens)
{
	(void)tokens;
	printf("\n--> PLANE <--\n");
	free_split(*tokens);
	return (SUCCESS);
}

int	parse_cylinder(char ***tokens)
{
	(void)tokens;
	printf("\n--> CYLINDER <--\n");
	free_split(*tokens);
	return (SUCCESS);
}
