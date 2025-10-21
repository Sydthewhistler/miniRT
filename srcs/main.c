#include "miniRT.h"

void debug_print_environment(t_environment *env);
void debug_print_objects(t_object *obj);

int main(int argc, char **argv)
{
	t_environment	*env;
	t_object		*obj;

	if(argc != 2)
	{
		printf("Usage: %s <scene_file.rt>\n", argv[0]);
		return (-1);
	}
	env = malloc(sizeof(t_environment));
	obj = malloc(sizeof(t_object));
	parsing_master(argv[1], &env, &obj);

	// Debug print after parsing
	debug_print_environment(env);
	debug_print_objects(obj);

	//process_rendering(env, obj);
	free_environment(env);
	free_objects(obj);
	return (0);
}

void debug_print_environment(t_environment *env)
{
    printf("\n=== ENVIRONMENT INFO ===\n");
    printf("Ambient Light:\n");
    printf("  Ratio: %f\n", env->ambient->ratio);
    printf("  Color: R:%d G:%d B:%d\n", 
        env->ambient->color.r,
        env->ambient->color.g,
        env->ambient->color.b);

    printf("\nCamera:\n");
    printf("  Position: x:%f y:%f z:%f\n",
        env->camera->position.x,
        env->camera->position.y,
        env->camera->position.z);
    printf("  Orientation: x:%f y:%f z:%f\n",
        env->camera->orientation.x,
        env->camera->orientation.y,
        env->camera->orientation.z);
    printf("  FOV: %d\n", env->camera->fov);

    printf("\nLight:\n");
    printf("  Position: x:%f y:%f z:%f\n",
        env->light->position.x,
        env->light->position.y,
        env->light->position.z);
    printf("  Brightness: %f\n", env->light->brightness);
    printf("  Color: R:%d G:%d B:%d\n",
        env->light->color.r,
        env->light->color.g,
        env->light->color.b);
}

void debug_print_objects(t_object *obj)
{
    t_sphere *sphere = obj->spheres;
    t_plane *plane = obj->planes;
    t_cylinder *cylinder = obj->cylinders;
    int i = 1;

    printf("\n=== OBJECTS INFO ===\n");
    
    // Print spheres
    while (sphere != NULL)
    {
        printf("\nSphere %d:\n", i++);
        printf("  Center: x:%f y:%f z:%f\n",
            sphere->center.x,
            sphere->center.y,
            sphere->center.z);
        printf("  Diameter: %f\n", sphere->diameter);
        printf("  Color: R:%d G:%d B:%d\n",
            sphere->color.r,
            sphere->color.g,
            sphere->color.b);
        sphere = sphere->next;
    }

    // Print planes
    while (plane != NULL)
    {
        printf("\nPlane %d:\n", i++);
        printf("  Point: x:%f y:%f z:%f\n",
            plane->point.x,
            plane->point.y,
            plane->point.z);
        printf("  Normal: x:%f y:%f z:%f\n",
            plane->normal.x,
            plane->normal.y,
            plane->normal.z);
        printf("  Color: R:%d G:%d B:%d\n",
            plane->color.r,
            plane->color.g,
            plane->color.b);
        plane = plane->next;
    }

    // Print cylinders
    while (cylinder != NULL)
    {
        printf("\nCylinder %d:\n", i++);
        printf("  Center: x:%f y:%f z:%f\n",
            cylinder->center.x,
            cylinder->center.y,
            cylinder->center.z);
        printf("  Axis: x:%f y:%f z:%f\n",
            cylinder->axis.x,
            cylinder->axis.y,
            cylinder->axis.z);
        printf("  Diameter: %f\n", cylinder->diameter);
        printf("  Height: %f\n", cylinder->height);
        printf("  Color: R:%d G:%d B:%d\n",
            cylinder->color.r,
            cylinder->color.g,
            cylinder->color.b);
        cylinder = cylinder->next;
    }
    
    printf("\n=== END OF DEBUG INFO ===\n");
}