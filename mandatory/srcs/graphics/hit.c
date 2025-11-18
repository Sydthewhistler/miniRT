/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprot <cprot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:10:17 by cprot             #+#    #+#             */
/*   Updated: 2025/11/18 11:05:20 by cprot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	rec->type = OBJ_SPHERE;
	rec->object = sphere;
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

static int	hit_plane(t_ray ray, t_plane *plane, t_hit_record *rec)
{
	double	t;
	double	denom;

	if (!intersect_plane(ray, plane, &t))
		return (0);
	if (t < 0.001 || t >= rec->t)
		return (0);
	rec->t = t;
	rec->point = vec_add(ray.origin, vec_scale(ray.direction, t));
	rec->type = OBJ_PLANE;
	rec->object = plane;
	// Déterminer l'orientation de la normale
	denom = vec_dot(ray.direction, plane->normal);
	if (denom < 0)
	{
		// Le rayon vient de face
		rec->front_face = 1;
		rec->normal = plane->normal;
	}
	else
	{
		// Le rayon vient de derrière
		rec->front_face = 0;
		rec->normal = vec_scale(plane->normal, -1.0);
	}
	return (1);
}

static int	hit_cylinder(t_ray ray, t_cylinder *cylinder, t_hit_record *rec)
{
	double	t;
	t_vec3	outward_normal;
	t_vec3	center_to_point;

	if (!intersect_cylinder_body(ray, cylinder, &t) || (t < 0.001
			|| t >= rec->t))
		return (0);
	rec->t = t;
	rec->point = vec_add(ray.origin, vec_scale(ray.direction, t));
	rec->type = OBJ_CYLINDER;
	rec->object = cylinder;
	// Calculer la normale (perpendiculaire à l'axe)
	center_to_point = vec_sub(rec->point, cylinder->center);
	// Projection sur l'axe
	outward_normal = vec_perp_to_axis(center_to_point, cylinder->axis);
	outward_normal = vec_normalize(outward_normal);
	// Déterminer front_face
	if (vec_dot(ray.direction, outward_normal) > 0)
	{
		rec->front_face = 0;
		rec->normal = vec_scale(outward_normal, -1.0);
	}
	else
	{
		rec->front_face = 1;
		rec->normal = outward_normal;
	}
	return (1);
}

int	hit_world(t_ray ray, t_object *obj, t_hit_record *rec)
{
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
	int			hit_anything;

	hit_anything = 0;
	// Tester les sphères
	sphere = obj->spheres;
	while (sphere)
	{
		if (hit_sphere(ray, sphere, rec))
			hit_anything = 1;
		sphere = sphere->next;
	}
	// Tester les plans
	plane = obj->planes;
	while (plane)
	{
		if (hit_plane(ray, plane, rec))
			hit_anything = 1;
		plane = plane->next;
	}
	// Tester les cylindres ← AJOUTER
	cylinder = obj->cylinders;
	while (cylinder)
	{
		if (hit_cylinder(ray, cylinder, rec))
			hit_anything = 1;
		cylinder = cylinder->next;
	}
	return (hit_anything);
}
