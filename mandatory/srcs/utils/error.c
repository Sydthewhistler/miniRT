#include "miniRT.h"

void exit_with_error(const char *message, t_environment **env, t_object **obj)
{
	perror(message);
	free_environment(*env);
	free_objects(*obj);
	exit(EXIT_FAILURE);
}