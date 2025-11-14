#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include "../../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <float.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_environment
{
	struct s_ambient	*ambient;
	struct s_camera		*camera;
	struct s_light		*light;
}						t_environment;

typedef struct s_object
{
	struct s_sphere		*spheres;
	struct s_plane		*planes;
	struct s_cylinder	*cylinders;
}						t_object;

// Vecteur 3D
typedef struct s_vec3
{
	double				x;
	double				y;
	double				z;
}						t_vec3;

// Couleur RGB
typedef struct s_color
{
	int					r;
	int					g;
	int					b;
}						t_color;

// Lumière ambiante (unique)
typedef struct s_ambient
{
	double ratio; // [0.0, 1.0]
	t_color				color;
}						t_ambient;

// Caméra (unique)
typedef struct s_camera
{
	t_vec3				position;
	t_vec3 orientation; // vecteur normalisé
	int fov;            // [0, 180]
}						t_camera;

// Lumière ponctuelle (unique en mandatory)
typedef struct s_light
{
	t_vec3				position;
	double brightness; // [0.0, 1.0]
	t_color color;     // non utilisé en mandatory
	struct s_light		*next;
}						t_light;

// Sphère
typedef struct s_sphere
{
	t_vec3				center;
	double				diameter;
	t_color				color;
	struct s_sphere *next; // liste chaînée
}						t_sphere;

// Plan
typedef struct s_plane
{
	t_vec3 point;         // point appartenant au plan
	t_vec3 normal;        // vecteur normalisé perpendiculaire au plan
	t_color color;        // couleur RGB
	struct s_plane *next; // pointeur vers le prochain plan (liste chaînée)
}						t_plane;

// Cylindre
typedef struct s_cylinder
{
	t_vec3 center;   // centre du cylindre
	t_vec3 axis;     // vecteur normalisé de l'axe du cylindre
	double diameter; // diamètre du cylindre
	double height;   // hauteur du cylindre
	t_color color;   // couleur RGB
	struct s_cylinder	*next;
	// pointeur vers le prochain cylindre (liste chaînée)
}						t_cylinder;

//		RENDERING FUNCTIONS        //

void					process_rendering(t_environment *env, t_object *obj);

//          PARSING FUNCTIONS         //

void					parsing_master(char *filename, t_environment **env,
							t_object **obj);
void					environment_parsing(char **line, t_environment **env,
							t_object **obj);
void					objects_parsing(char **line, t_environment **env,
							t_object **obj);

void					parse_ambient(char **line, t_environment **env);
void					parse_camera(char **line, t_environment **env,
							t_object **obj);
void					parse_light(char **line, t_environment **env);
void					parse_sphere(char **line, t_environment **env,
							t_object **obj);
void					parse_plane(char **line, t_environment **env,
							t_object **obj);
void					parse_cylinder(char **line, t_environment **env,
							t_object **obj);

double					parse_double(char *str, double min, double max,
							t_environment **env);
int						parse_int(char *str, int min, int max,
							t_environment **env);
t_color					parse_color(char *str, t_environment **env);
t_vec3					parse_vector(char *str, t_environment **env);
t_vec3					parse_vector_range(char *str, double min, double max,
							t_environment **env);

//        FREE FUNCTIONS          //

void					free_environment(t_environment *env);
void					free_objects(t_object *obj);
void					free_tab(char **tab);

//              UTILS                  //

void					exit_with_error(const char *message,
							t_environment **env, t_object **obj);

#endif