#ifndef MINIRT_TEST_H
# define MINIRT_TEST_H

# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <float.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 800
# define HEIGHT 600

// ------------------------------------------------------
// STRUCTURES PRINCIPALES
// ------------------------------------------------------

typedef struct s_vec3
{
	double				x;
	double				y;
	double				z;
}						t_vec3;

typedef struct s_color
{
	int					r;
	int					g;
	int					b;
}						t_color;

typedef struct s_ambient
{
	double				ratio;
	t_color				color;
}						t_ambient;

typedef struct s_camera
{
	t_vec3				position;
	t_vec3				orientation;
	int					fov;
}						t_camera;

typedef struct s_light
{
	t_vec3				position;
	double				brightness;
	t_color				color;
}						t_light;

typedef struct s_sphere
{
	t_vec3				center;
	double				diameter;
	t_color				color;
	struct s_sphere		*next;
}						t_sphere;

typedef struct s_plane
{
	t_vec3				point;
	t_vec3				normal;
	t_color				color;
	struct s_plane		*next;
}						t_plane;

typedef struct s_cylinder
{
	t_vec3				center;
	t_vec3				axis;
	double				diameter;
	double				height;
	t_color				color;
	struct s_cylinder	*next;
}						t_cylinder;

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

// ------------------------------------------------------
// STRUCTURES AJOUTEES
// ------------------------------------------------------

typedef struct s_minirt
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	t_environment		*env;
	t_object			*obj;
}						t_minirt;

typedef struct s_ray
{
	t_vec3				origin;
	t_vec3				direction;
}						t_ray;

typedef struct s_camera_basis
{
	t_vec3				forward;
	t_vec3				right;
	t_vec3				up;
	double				viewport_width;
	double				viewport_height;
}						t_camera_basis;

// ------------------------------------------------------
// FONCTIONS UTILITAIRES / RENDU
// ------------------------------------------------------

// void	process_rendering(t_environment *env, t_object *obj);
void					free_environment(t_environment *env);
void					free_objects(t_object *obj);
void					exit_with_error(const char *message,
							t_environment **env, t_object **obj);

// ------------------------------------------------------
// FONCTIONS AJOUTEES
// ------------------------------------------------------

void					init_miniRT(t_environment *env, t_object *obj);
void					apply_hooks(t_minirt *rt);
int						close_window(t_minirt *rt);

void					setup_camera(t_minirt *rt, t_camera_basis *cam);

// Vecteurs
t_vec3					vec_add(t_vec3 a, t_vec3 b);
t_vec3					vec_sub(t_vec3 a, t_vec3 b);
t_vec3					vec_scale(t_vec3 v, double s);
double					vec_dot(t_vec3 a, t_vec3 b);
double					vec_length(t_vec3 v);
t_vec3					vec_normalize(t_vec3 v);
t_vec3					vec_cross(t_vec3 a, t_vec3 b);

#endif
