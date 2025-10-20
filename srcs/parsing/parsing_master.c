#include "miniRT.h"

void parsing_master(char *filename, t_environment **env, t_object **obj)
{
	int fd;
	char **line;

	fd=	open(filename, O_RDONLY);
	if (fd < 0)
	{
		exit_with_error("Error opening file",env,obj);
	}
	while(1)
	{
		line = ft_split(get_next_line(fd), " ");
		if (!line)
			break;
		if(line[0][0] == 'A' || line[0][0] == 'C' || line[0][0] == 'L')
			environment_parsing(line, env, obj);
		else if(!ft_strcmp(line[0], "sp") || !ft_strcmp(line[0], "pl") || !ft_strcmp(line[0], "cy"))
			objects_parsing(line, env, obj);
		else
		{
			exit_with_error("Error\n",env,obj);
		}
		free_tab(line);
	}
}

void environment_parsing(char **line, t_environment **env, t_object **obj)
{
	if(line[0][0] == 'A')
	{
		if((*env)->ambient)
			exit_with_error("Error\n", env, obj);
		(*env)->ambient = malloc(sizeof(t_ambient));
		parse_ambient(line, env);
	}
	else if(line[0][0] == 'C')
	{
		if((*env)->camera)
			exit_with_error("Error\n", env, obj);
		parse_camera(line, env);
	}
	else if(line[0][0] == 'L')
	{
		if((*env)->light)
			exit_with_error("Error\n", env, obj);
		parse_light(line, env);
	}
}

void objects_parsing(char **line,t_environment **env ,t_object **obj)
{
	if(!ft_strcmp(line[0], "sp"))
		parse_sphere(line, env, obj);
	else if(!ft_strcmp(line[0], "pl"))
		parse_plane(line, env, obj);
	else if(!ft_strcmp(line[0], "cy"))
		parse_cylinder(line, env, obj);
}