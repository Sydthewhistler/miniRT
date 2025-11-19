/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprot <cprot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:09:46 by cprot             #+#    #+#             */
/*   Updated: 2025/11/19 16:39:12 by cprot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"
/*
** Intersection rayon-plan
** Équation du plan: (P - point) · normal = 0
** Équation du rayon: P = origin + t * direction
**
** Substitution: ((origin + t * direction) - point) · normal = 0
** Développement: (origin - point) · normal + t * (direction · normal) = 0
** Solution: t = -((origin - point) · normal) / (direction · normal)
*/

int	intersect_plane(t_ray ray, t_plane *plane, double *t)
{
	double	denom;
	double	numer;
	t_vec3	oc;

	// Calculer le dénominateur (direction · normal)
	denom = vec_dot(ray.direction, plane->normal);
	// Si denom ≈ 0, le rayon est parallèle au plan (pas d'intersection)
	if (fabs(denom) < 0.0001)
		return (0);
	// Calculer le numérateur ((point - origin) · normal)
	oc = vec_sub(plane->point, ray.origin);
	numer = vec_dot(oc, plane->normal);
	// Calculer t
	*t = numer / denom;
	// Le rayon doit aller vers l'avant (t > 0)
	if (*t < 0)
		return (0);
	return (1);
}
