#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_environment	*env;
	t_object		*obj;

	if(argc != 2)
	{
		printf("Usage: %s <scene_file.rt>\n", argv[0]);
		return (-1);
	}
	parsing_master(argv[1], &env, &obj);
	process_rendering(env, obj);
	free_environment(env);
	free_objects(obj);
	return (0);
}