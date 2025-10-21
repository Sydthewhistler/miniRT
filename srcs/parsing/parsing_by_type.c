#include "miniRT.h"


void parse_ambient(char **line, t_environment **env)
{
	(*env)->ambient = malloc(sizeof(t_ambient));
	(*env)->ambient->ratio = parse_double(line[1], 0.0, 1.0, env); 
	(*env)->ambient->color = parse_color(line[2], env);
}

void parse_camera(char **line, t_environment **env, t_object **obj)
{
	(*env)->camera = malloc(sizeof(t_camera));
	(*env)->camera->position = parse_vector(line[1], env);
	(*env)->camera->orientation = parse_vector_range(line[2], -1.0, 1.0, env);
	(*env)->camera->fov = atoi(line[3]);
	if((*env)->camera->fov < 0 || (*env)->camera->fov > 180)
		exit_with_error("Error: FOV out of range\n", env,obj);
}

void parse_light(char **line, t_environment **env)
{
	(*env)->light = malloc(sizeof(t_light));
	(*env)->light->position = parse_vector(line[1], env);
	(*env)->light->brightness = parse_double(line[2], 0.0, 1.0, env);
	(*env)->light->color = parse_color(line[3], env);
}

void parse_sphere(char **line, t_environment **env, t_object **obj)
{
	t_sphere *new_sphere;

	new_sphere = malloc(sizeof(t_sphere));
	new_sphere->center = parse_vector(line[1], env);
	new_sphere->diameter = parse_double(line[2], 0.0, DBL_MAX, env);
	new_sphere->color = parse_color(line[3], env);
	new_sphere->next = NULL;

	if (!(*obj)->spheres)
		(*obj)->spheres = new_sphere;
	else
	{
		t_sphere *temp = (*obj)->spheres;
		while (temp->next)
			temp = temp->next;
		temp->next = new_sphere;
	}
}

void parse_plane(char **line, t_environment **env, t_object **obj)
{
	t_plane *new_plane;

	new_plane = malloc(sizeof(t_plane));
	new_plane->point = parse_vector(line[1], env);
	new_plane->normal = parse_vector_range(line[2], -1.0, 1.0, env);
	new_plane->color = parse_color(line[3], env);
	new_plane->next = NULL;

	if (!(*obj)->planes)
		(*obj)->planes = new_plane;
	else
	{
		t_plane *temp = (*obj)->planes;
		while (temp->next)
			temp = temp->next;
		temp->next = new_plane;
	}
}

void	parse_cylinder(char **line, t_environment **env, t_object **obj)
{
	t_cylinder *new_cylinder;

	new_cylinder = malloc(sizeof(t_cylinder));
	new_cylinder->center = parse_vector(line[1], env);
	new_cylinder->axis = parse_vector_range(line[2], -1.0, 1.0, env);
	new_cylinder->diameter = parse_double(line[3], 0.0, DBL_MAX, env);
	new_cylinder->height = parse_double(line[4], 0.0, DBL_MAX, env);
	new_cylinder->color = parse_color(line[5], env);
	new_cylinder->next = NULL;

	if (!(*obj)->cylinders)
		(*obj)->cylinders = new_cylinder;
	else
	{
		t_cylinder *temp = (*obj)->cylinders;
		while (temp->next)
			temp = temp->next;
		temp->next = new_cylinder;
	}
}