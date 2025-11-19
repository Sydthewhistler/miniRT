/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_master.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scavalli <scavalli@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:09:23 by cprot             #+#    #+#             */
/*   Updated: 2025/11/19 11:27:02 by scavalli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	find_type(char **line, t_environment **env, t_object **obj)
{
	if (ft_strcmp(line[0], "A") == 0 || ft_strcmp(line[0], "C") == 0
		|| ft_strcmp(line[0], "L") == 0)
		environment_parsing(line, env, obj);
	else if (!ft_strcmp(line[0], "sp") || !ft_strcmp(line[0], "pl")
		|| !ft_strcmp(line[0], "cy"))
		objects_parsing(line, env, obj);
	else
	{
		exit_with_error("Error\nInvalid identifier", env, obj);
	}
	free_tab(line);
}

void	parsing_master(char *filename, t_environment **env, t_object **obj)
{
	int		fd;
	char	**line;
	char	*gnl_line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_with_error("Error opening file", env, obj);
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
		exit_with_error("Error closing file", env, obj);
	if (!(*env)->ambient || !(*env)->camera || !(*env)->light)
		exit_with_error("Error\nMissing essential elements", env, obj);
}

void	environment_parsing(char **line, t_environment **env, t_object **obj)
{
	if (line[0][0] == 'A')
	{
		if ((*env)->ambient || ft_lentab(line) != 3)
			exit_with_error("Error\nAmbient lighting already defined or has invalid arguments",
				env, obj);
		parse_ambient(line, env);
	}
	else if (line[0][0] == 'C')
	{
		if ((*env)->camera || ft_lentab(line) != 4)
			exit_with_error("Error\nCamera already defined or has invalid arguments",
				env, obj);
		parse_camera(line, env, obj);
	}
	else if (line[0][0] == 'L')
	{
		if ((*env)->light || ft_lentab(line) != 4)
			exit_with_error("Error\nLight already defined or has invalid arguments",
				env, obj);
		parse_light(line, env);
	}
}

void	objects_parsing(char **line, t_environment **env, t_object **obj)
{
	if (!ft_strcmp(line[0], "sp"))
	{
		if (ft_lentab(line) != 4)
			exit_with_error("Error\nInvalid sphere definition", env, obj);
		parse_sphere(line, env, obj);
	}
	else if (!ft_strcmp(line[0], "pl"))
	{
		if (ft_lentab(line) != 4)
			exit_with_error("Error\nInvalid plane definition", env, obj);
		parse_plane(line, env, obj);
	}
	else if (!ft_strcmp(line[0], "cy"))
	{
		if (ft_lentab(line) != 6)
			exit_with_error("Error\nInvalid cylinder definition", env, obj);
		parse_cylinder(line, env, obj);
	}
}
