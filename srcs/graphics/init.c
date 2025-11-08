#include "miniRT.h"

void	my_mlx_pixel_put(t_minirt *rt, int x, int y, int color)
{
	char	*dst;

	dst = rt->addr + (y * rt->line_length + x * (rt->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	init_miniRT(t_environment *env, t_object *obj)
{
	t_minirt rt;

	// Stocker env et obj
	rt.env = env;
	rt.obj = obj;
	// Init MLX
	rt.mlx = mlx_init();
	rt.win = mlx_new_window(rt.mlx, WIDTH, HEIGHT, "miniRT");
	// Créer l'image
	rt.img = mlx_new_image(rt.mlx, WIDTH, HEIGHT);
	rt.addr = mlx_get_data_addr(rt.img, &rt.bits_per_pixel, &rt.line_length,
			&rt.endian);
	// TODO: Dessiner vos pixels
	my_mlx_pixel_put(&rt, 100, 100, 0x00FF0000);
	// Afficher
	mlx_put_image_to_window(rt.mlx, rt.win, rt.img, 0, 0);
	// Hooks
	apply_hooks(&rt);
	// Loop
	mlx_loop(rt.mlx);
}