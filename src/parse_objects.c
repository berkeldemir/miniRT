#include "../inc/mini.h"

int	parse_sphere(char ***tokens)
{
	t_obj	*obj;

	printf("--> SPHERE <--\n");
	if (!tokens || !*tokens || !(*tokens)[1] || !(*tokens)[2] || !(*tokens)[3])
		return (FAIL);
	obj = ft_calloc(sizeof(t_obj), 1);
	if (!obj)
		return (FAIL);
	obj->type = SPHERE;
	if (rt_coords(&obj->coords, (*tokens)[1], FALSE) == FAIL || \
		rt_atod((*tokens)[2], 0.0, 999999.0, &obj->diameter) == FAIL || \
		rt_color(&obj->color, (*tokens)[3]) == FAIL)
		return (free(obj), free_split(*tokens), FAIL);
	free_split(*tokens);
	/*printf("Type   : %c\n", obj->type);
	printf("Coords : %f\t%f\t%f\n", obj->coords.x,  obj->coords.y, obj->coords.z);
	printf("normal: %f\t%f\t%f\n", obj->normal.x,  obj->normal.y, obj->normal.z);
	printf("Diamet.: %f\n", obj->diameter);
	printf("Height : %f\n\n", obj->height);*/
	ft_lstadd_back(&mini()->objs, ft_lstnew(obj));
	return (SUCCESS);
}

int	parse_plane(char ***tokens)
{
	t_obj	*obj;

	printf("--> PLANE <--\n");
	if (!tokens || !*tokens || !(*tokens)[1] || !(*tokens)[2] || !(*tokens)[3])
		return (FAIL);
	obj = ft_calloc(sizeof(t_obj), 1);
	if (!obj)
		return (FAIL);
	obj->type = PLANE;
	if (rt_coords(&obj->coords, (*tokens)[1], FALSE) == FAIL || \
		rt_coords(&obj->normal, (*tokens)[2], TRUE) == FAIL || \
		rt_color(&obj->color, (*tokens)[3]) == FAIL)
		return (free(obj), free_split(*tokens), FAIL);
	free_split(*tokens);
	/*printf("Type   : %c\n", obj->type);
	printf("Coords : %f\t%f\t%f\n", obj->coords.x,  obj->coords.y, obj->coords.z);
	printf("normal: %f\t%f\t%f\n", obj->normal.x,  obj->normal.y, obj->normal.z);
	printf("Diamet.: %f\n", obj->diameter);
	printf("Height : %f\n\n", obj->height);*/
	ft_lstadd_back(&mini()->objs, ft_lstnew(obj));
	return (SUCCESS);
}

int	parse_cylinder(char ***tokens)
{
	t_obj	*obj;

	printf("--> CYLINDER <--\n");
	if (!tokens || !*tokens || !(*tokens)[1] || !(*tokens)[2] || !(*tokens)[3] || !(*tokens)[4] || !(*tokens)[5])
		return (FAIL);
	obj = ft_calloc(sizeof(t_obj), 1);
	if (!obj)
		return (FAIL);
	obj->type = CYLINDER;
	if (rt_coords(&obj->coords, (*tokens)[1], FALSE) == FAIL || 
		rt_coords(&obj->normal, (*tokens)[2], TRUE) == FAIL || \
		rt_atod((*tokens)[3], 0.0, 999999.0, &obj->diameter) == FAIL || \
		rt_atod((*tokens)[4], 0.0, 999999.0, &obj->height) == FAIL || \
		rt_color(&obj->color, (*tokens)[5]) == FAIL)
		return (free(obj), free_split(*tokens), FAIL);
	free_split(*tokens);
	/*printf("Type   : %c\n", obj->type);
	printf("Coords : %f\t%f\t%f\n", obj->coords.x,  obj->coords.y, obj->coords.z);
	printf("normal: %f\t%f\t%f\n", obj->normal.x,  obj->normal.y, obj->normal.z);
	printf("Diamet.: %f\n", obj->diameter);
	printf("Height : %f\n\n", obj->height);*/
	ft_lstadd_back(&mini()->objs, ft_lstnew(obj));
	return (SUCCESS);
}
