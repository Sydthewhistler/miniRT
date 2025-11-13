#include "miniRT.h"

static int	hit_sphere(t_ray ray, t_sphere *sphere, t_hit_record *rec)
{
	double	t;
	t_vec3	outward_normal;

	if (!intersect_sphere(ray, sphere, &t))
		return (0);
	if (t < 0.001 || t >= rec->t)
		return (0);
	rec->t = t;
	rec->point = vec_add(ray.origin, vec_scale(ray.direction, t));
	rec->hit_sphere = sphere;
	// Étape 1 : Calculer la normale sortante (du centre vers le point)
	outward_normal = vec_sub(rec->point, sphere->center);
	outward_normal = vec_normalize(outward_normal);
	// Étape 2 : Tester si le rayon vient de l'intérieur ou l'extérieur
	if (vec_dot(ray.direction, outward_normal) > 0)
	{
		// Rayon et normale dans la MÊME direction
		// → Le rayon vient de l'INTÉRIEUR
		rec->front_face = 0;
		rec->normal = vec_scale(outward_normal, -1.0); // Inverser
	}
	else
	{
		// Rayon et normale dans des directions OPPOSÉES
		// → Le rayon vient de l'EXTÉRIEUR
		rec->front_face = 1;
		rec->normal = outward_normal;
	}
	return (1);
}

int	hit_world(t_ray ray, t_object *obj, t_hit_record *rec)
{
	t_sphere	*sphere;
	int			hit_anything;
	double		closest_so_far;

	// t_plane     *plane;      // Décommente quand tu codes les plans
	// t_cylinder  *cylinder;   // Décommente quand tu codes les cylindres
	hit_anything = 0;
	closest_so_far = rec->t;
	// Tester les sphères
	sphere = obj->spheres;
	while (sphere)
	{
		if (hit_sphere(ray, sphere, rec))
		{
			hit_anything = 1;
			closest_so_far = rec->t;
		}
		sphere = sphere->next;
	}
	// Plans - À implémenter plus tard
	// plane = obj->planes;
	// while (plane) { ... }
	// Cylindres - À implémenter plus tard
	// cylinder = obj->cylinders;
	// while (cylinder) { ... }
	return (hit_anything);
}