/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprot <cprot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:11:54 by cprot             #+#    #+#             */
/*   Updated: 2025/12/01 12:28:51 by cprot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	exit_with_error(const char *message, t_environment **env,
		t_object **obj, char **line)
{
	if (message)
		printf("Error\n%s\n", message);
	else
		printf("Error\n");
	get_next_line(-1);
	free_environment(*env);
	free_objects(*obj);
	free_tab(line);
	exit(EXIT_FAILURE);
}void	parse_ambient(char **line, t_environment **env)
{
	(*env)->ambient = malloc(sizeof(t_ambient));
	if (!(*env)->ambient)
		exit_with_error("Memory allocation failed for ambient\n", env,
			NULL, NULL);
	(*env)->ambient->ratio = parse_double(line[1], 0.0, 1.0, env);
	(*env)->ambient->color = parse_color(line[2], env);
}

void	parse_camera(char **line, t_environment **env, t_object **obj)
{
	(*env)->camera = malloc(sizeof(t_camera));
	if (!(*env)->camera)
		exit_with_error("Memory allocation failed for camera\n", env,
			obj, NULL);
	(*env)->camera->position = parse_vector(line[1], env);
	(*env)->camera->orientation = parse_vector_range(line[2], -1.0, 1.0, env);
	(*env)->camera->fov = atoi(line[3]);
	if ((*env)->camera->fov < 0 || (*env)->camera->fov > 180)
		exit_with_error("FOV out of range\n", env, obj, NULL);
}
