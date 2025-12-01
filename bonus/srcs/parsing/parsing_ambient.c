/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_ambient.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprot <cprot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 10:53:52 by scavalli          #+#    #+#             */
/*   Updated: 2025/12/01 12:55:47 by cprot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"
void	parse_ambient(char **line, t_environment **env)
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
	(*env)->camera->fov = ft_atoi(line[3]);
	if ((*env)->camera->fov < 0 || (*env)->camera->fov > 180)
		exit_with_error("FOV out of range\n", env, obj, NULL);
}

void	parse_light(char **line, t_environment **env)
{
	t_light	*new_light;
	t_light	*temp;

	new_light = malloc(sizeof(t_light));
	if (!new_light)
		exit_with_error("Memory allocation failed\n", env, NULL, NULL);
	new_light->position = parse_vector(line[1], env);
	new_light->brightness = parse_double(line[2], 0.0, 1.0, env);
	new_light->color = parse_color(line[3], env);
	new_light->next = NULL;
	if (!(*env)->light)
		(*env)->light = new_light;
	else
	{
		temp = (*env)->light;
		while (temp->next)
			temp = temp->next;
		temp->next = new_light;
	}
}
