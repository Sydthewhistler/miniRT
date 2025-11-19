/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprot <cprot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:11:54 by cprot             #+#    #+#             */
/*   Updated: 2025/11/19 16:40:09 by cprot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	exit_with_error(const char *message, t_environment **env,
		t_object **obj)
{
	if (message)
		printf("%s\n", message);
	else
		printf("Error\n");
	free_environment(*env);
	free_objects(*obj);
	exit(EXIT_FAILURE);
}
