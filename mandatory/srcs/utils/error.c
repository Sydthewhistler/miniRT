/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprot <cprot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:11:54 by cprot             #+#    #+#             */
/*   Updated: 2025/11/18 11:12:39 by cprot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void exit_with_error(const char *message, t_environment **env, t_object **obj)
{
	perror(message);
	free_environment(*env);
	free_objects(*obj);
	exit(EXIT_FAILURE);
}
