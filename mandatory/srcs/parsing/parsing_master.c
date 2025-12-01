/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_master.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprot <cprot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:09:23 by cprot             #+#    #+#             */
/*   Updated: 2025/12/01 12:26:29 by cprot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	find_type(char **line, t_environment **env, t_object **obj)
{
	if (ft_strcmp(line[0], "A") == 0 || ft_strcmp(line[0], "C") == 0
		|| ft_strcmp(line[0], "L") == 0)
		environment_parsing(line, env, obj);
	else if (!ft_strcmp(line[0], "sp") || !ft_strcmp(line[0], "pl")
		|| !ft_strcmp(line[0], "cy"))
		objects_parsing(line, env, obj);
	else
		exit_with_error("Invalid identifier", env, obj, line);
	free_tab(line);
}

void	parsing_master(char *filename, t_environment **env, t_object **obj)
{
	int		fd;
	char	**line;
	char	*gnl_line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_with_error("Error opening file", env, obj, NULL);
	while (1)
	{
		gnl_line = get_next_line(fd);
		if (!gnl_line)
			break ;
		line = ft_split(gnl_line, " \t\n");
		free(gnl_line);
		if (!line[0] || line[0][0] == '\n')
		{
			free_tab(line);
			continue ;
		}
		find_type(line, env, obj);
	}
	if (close(fd) < 0)
		exit_with_error("Error closing file", env, obj, NULL);
	if (!(*env)->ambient || !(*env)->camera || !(*env)->light)
		exit_with_error("Missing essential elements", env, obj, NULL);
}

static void	environment_parsing2(char **line, t_environment **env, t_object **obj)
{
	if (line[0][0] == 'L')
	{
		if ((*env)->light || ft_lentab(line) != 4
			|| !verify_light((const char **)line))
			exit_with_error(LIGHT_ERROR, env, obj, line);
		parse_light(line, env);
	}
}

void	environment_parsing(char **line, t_environment **env, t_object **obj)
{
	if (line[0][0] == 'A')
	{
		if ((*env)->ambient || ft_lentab(line) != 3
			|| !verify_ambient((const char **)line))
			exit_with_error(AMBIENT_ERROR, env, obj, line);
		parse_ambient(line, env);
	}
	else if (line[0][0] == 'C')
	{
		if ((*env)->camera || ft_lentab(line) != 4
			|| !verify_camera_((const char **)line))
			exit_with_error(CAMERA_ERROR, env, obj, line);
		parse_camera(line, env, obj);
	}
	else
		environment_parsing2(line, env, obj);
}

void	objects_parsing(char **line, t_environment **env, t_object **obj)
{
	if (!ft_strcmp(line[0], "sp"))
	{
		if (ft_lentab(line) != 4 || !verify_sphere((const char **)line))
			exit_with_error("Invalid sphere definition", env, obj,
				line);
		parse_sphere(line, env, obj);
	}
	else if (!ft_strcmp(line[0], "pl"))
	{
		if (ft_lentab(line) != 4 || !verify_plane((const char **)line))
			exit_with_error("Invalid plane definition", env, obj, line);
		parse_plane(line, env, obj);
	}
	else if (!ft_strcmp(line[0], "cy"))
	{
		if (ft_lentab(line) != 6 || !verify_cylinder((const char **)line))
			exit_with_error("Invalid cylinder definition", env, obj,
				line);
		parse_cylinder(line, env, obj);
	}
}
