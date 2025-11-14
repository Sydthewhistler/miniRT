#include "miniRT.h"

static void	init_cylinder_calc(t_cylinder_calc *calc, t_vec3 oc, t_vec3 dir,
		t_vec3 axis, double radius)
{
	calc->oc_perp = vec_perp_to_axis(oc, axis);
	calc->dir_perp = vec_perp_to_axis(dir, axis);
	calc->a = vec_dot(calc->dir_perp, calc->dir_perp);
	calc->b = 2.0 * vec_dot(calc->oc_perp, calc->dir_perp);
	calc->c = vec_dot(calc->oc_perp, calc->oc_perp) - radius * radius;
}

static double	get_discriminant(t_cylinder_calc *calc)
{
	return (calc->b * calc->b - 4.0 * calc->a * calc->c);
}

static int	solve_for_t(t_cylinder_calc *calc, double discriminant, double *t)
{
	double	sqrt_disc;
	double	t1;
	double	t2;

	sqrt_disc = sqrt(discriminant);
	t1 = (-calc->b - sqrt_disc) / (2.0 * calc->a);
	t2 = (-calc->b + sqrt_disc) / (2.0 * calc->a);
	if (t1 > 0.001)
		*t = t1;
	else if (t2 > 0.001)
		*t = t2;
	else
		return (0);
	return (1);
}

static int	check_height_optimized(t_ray ray, t_cylinder *cyl, double t,
		t_vec3 oc)
{
	double	oc_parallel;
	double	dir_parallel;
	double	point_parallel;

	oc_parallel = vec_dot(oc, cyl->axis);
	dir_parallel = vec_dot(ray.direction, cyl->axis);
	point_parallel = oc_parallel + t * dir_parallel;
	if (point_parallel < -cyl->height / 2.0 || point_parallel > cyl->height
		/ 2.0)
		return (0);
	return (1);
}

int	intersect_cylinder_body(t_ray ray, t_cylinder *cyl, double *t)
{
	t_vec3 oc;
	t_cylinder_calc calc;
	double discriminant;

	oc = vec_sub(ray.origin, cyl->center);
	init_cylinder_calc(&calc, oc, ray.direction, cyl->axis, cyl->diameter
		/ 2.0);
	discriminant = get_discriminant(&calc);
	if (discriminant < 0)
		return (0);
	if (!solve_for_t(&calc, discriminant, t))
		return (0);
	return (check_height_optimized(ray, cyl, *t, oc));
}