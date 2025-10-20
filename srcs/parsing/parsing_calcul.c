#include "miniRT.h"

double	parse_double(char *str, double min, double max, t_environment **env)
{
	double	value;

	if (!str)
		exit_with_error("Error\n", env, NULL);
	value = ft_atof(str);
	if (value < min || value > max)
		exit_with_error("Error\n", env, NULL);
	return (value);
}

t_color parse_color(char *str, t_environment **env)
{
	t_color color;
	char **components;
	int r, g, b;

	components = ft_split(str, ",");
	if (!components || ft_tablen(components) != 3)
	{
		exit_with_error("Error\n", env, NULL);
	}
	r = parse_int(components[0], 0, 255, env);
	g = parse_int(components[1], 0, 255, env);
	b = parse_int(components[2], 0, 255, env);
	color.r = r;
	color.g = g;
	color.b = b;
	free_tab(components);
	return (color);
}

t_vec3 parse_vector(char *str, t_environment **env)
{
	t_vec3 vec;
	char **components;

	components = ft_split(str, ",");
	if (!components || ft_tablen(components) != 3)
	{
		exit_with_error("Error\n", env, NULL);
	}
	vec.x = parse_double(components[0], -DBL_MAX, DBL_MAX, env);
	vec.y = parse_double(components[1], -DBL_MAX, DBL_MAX, env);
	vec.z = parse_double(components[2], -DBL_MAX, DBL_MAX, env);
	free_tab(components);
	return (vec);
}

t_vec3	parse_vector_range(char *str, double min, double max, t_environment **env)
{
	t_vec3 vec;

	vec = parse_vector(str, env);
	if (vec.x < min || vec.x > max || vec.y < min || vec.y > max || vec.z < min || vec.z > max)
	{
		exit_with_error("Error\n", env, NULL);
	}
	return (vec);
}
