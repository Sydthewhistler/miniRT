#include "miniRT.h"

void	setup_camera(t_minirt *rt, t_camera_basis *cam)
{
	t_vec3 world_up;
	double aspect_ratio;
	double fov_rad;
	double viewport_height;
	double viewport_width;

	cam->forward = vec_normalize(rt->env->camera->orientation);
	if (fabs(cam->forward.y) > 0.999)
		world_up = (t_vec3){1.0, 0.0, 0.0};
	else
		world_up = (t_vec3){0.0, 1.0, 0.0};
	cam->right = vec_normalize(vec_cross(cam->forward, world_up));
	cam->up = vec_cross(cam->right, cam->forward);
	aspect_ratio = WIDTH / HEIGHT;
	fov_rad = (rt->env->camera->fov) * M_PI / 180.0;
	viewport_height = 2.0 * tan(fov_rad / 2.0);
	viewport_width = viewport_height * aspect_ratio;
	cam->viewport_width = viewport_width;
	cam->viewport_height = viewport_height;
}