/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprot <cprot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:11:54 by cprot             #+#    #+#             */
/*   Updated: 2025/11/26 13:47:11 by cprot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	exit_with_error(const char *message, t_environment **env,
		t_object **obj, char **line)
{
	if (message)
		printf("%s\n", message);
	else
		printf("Error\n");
	get_next_line(-1);
	free_environment(*env);
	free_objects(*obj);
	free_tab(line);
	exit(EXIT_FAILURE);
}
