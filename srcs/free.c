#include "miniRT.h"

void	free_environment(t_environment *env)
{
	if (!env)
		return ;
	if (env->ambient)
		free(env->ambient);
	if (env->camera)
		free(env->camera);
	if (env->light)
		free(env->light);
	free(env);
}

void	free_objects(t_object *obj)
{
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cyl;
	void		*next;

	if (!obj)
		return ;
	/* Free spheres */
	sphere = obj->spheres;
	while (sphere)
	{
		next = sphere->next;
		free(sphere);
		sphere = next;
	}
	/* Free planes */
	plane = obj->planes;
	while (plane)
	{
		next = plane->next;
		free(plane);
		plane = next;
	}
	/* Free cylinders */
	cyl = obj->cylinders;
	while (cyl)
	{
		next = cyl->next;
		free(cyl);
		cyl = next;
	}
	free(obj);
}

void	exit_with_error(const char *message, t_environment **env,
		t_object **obj)
{
	printf("Error\n%s\n", message);
	if (env && *env)
		free_environment(*env);
	if (obj && *obj)
		free_objects(*obj);
	exit(1);
}
