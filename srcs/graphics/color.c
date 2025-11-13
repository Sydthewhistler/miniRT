#include "miniRT.h"

int	vec3_to_int(t_vec3 v)
{
	int	r;
	int	g;
	int	b;

	r = (int)(255.999 * v.x);
	g = (int)(255.999 * v.y);
	b = (int)(255.999 * v.z);
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	if (r < 0)
		r = 0;
	if (g < 0)
		g = 0;
	if (b < 0)
		b = 0;
	return ((r << 16) | (g << 8) | b);
}

t_vec3	color_to_vec3(int r, int g, int b)
{
	t_vec3	new;

	new.x = r / 255.0;
	new.y = g / 255.0;
	new.z = b / 255.0;
	return (new);
}

static t_vec3	calculate_lighting(t_hit_record *rec, t_sphere *sphere,
		t_environment *env)
{
	t_vec3	obj_color;
	t_vec3	ambient;
	t_vec3	light_dir;
	t_vec3	diffuse;
	double	diff;

	obj_color = color_to_vec3(sphere->color.r, sphere->color.g,
			sphere->color.b);
	ambient = vec_mult(obj_color, color_to_vec3(env->ambient->color.r,
				env->ambient->color.g, env->ambient->color.b));
	ambient = vec_scale(ambient, env->ambient->ratio);
	light_dir = vec_sub(env->light->position, rec->point);
	light_dir = vec_normalize(light_dir);
	diff = vec_dot(rec->normal, light_dir);
	if (diff < 0.0)
		diff = 0.0;
	// parce que si diff est <0 c est que la light est apres l obj
	diffuse = vec_scale(obj_color, env->light->brightness * diff);
	// combinaison ambiante + diffuse
	return (vec_add(ambient, diffuse));
}

t_vec3	ray_color(t_ray ray, t_object *obj, t_environment *env)
{
	t_hit_record	rec;

	rec.t = DBL_MAX;
	if (hit_world(ray, obj, &rec))
	{
		return (calculate_lighting(&rec, rec.hit_sphere, env));
	}
	return ((t_vec3){0, 0, 0});
}
