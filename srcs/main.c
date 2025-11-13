#include "miniRT.h"

int	main(void)
{
	t_environment env;
	t_object obj;
	t_ambient ambient;
	t_camera camera;
	t_light light;
	static t_sphere sphere1; // ← static
	static t_sphere sphere2; // ← static
	static t_sphere sphere3; // ← static
	t_plane plane;
	t_cylinder cylinder;

	// A 0.2 255,255,255
	ambient.ratio = 0.15; // Moins d'ambient = plus de contraste
	ambient.color.r = 255;
	ambient.color.g = 255;
	ambient.color.b = 255;

	// CAMÉRA - Vue en plongée légère
	camera.position.x = -60.0;
	camera.position.y = 25.0; // En hauteur sur le côté
	camera.position.z = 35.0; // Surélevée
	camera.orientation.x = 0.85;
	camera.orientation.y = -0.35;
	camera.orientation.z = -0.40;
	camera.fov = 70;
	camera.samples_per_pixel = QUALITY;

	// LUMIÈRE - Bien placée pour créer des ombres
	light.position.x = -20.0; // Plus proche des objets
	light.position.y = 30.0;  // En hauteur
	light.position.z = 40.0;  // Au-dessus
	light.brightness = 0.8;   // Plus intense
	light.color.r = 255;
	light.color.g = 255;
	light.color.b = 255;

	// SPHÈRE 1 : GROSSE CYAN - Arrière-plan bas
	sphere1.center.x = 25.0;
	sphere1.center.y = -10.0; // En bas
	sphere1.center.z = 18.0;
	sphere1.diameter = 30.0; // Très grosse
	sphere1.color.r = 0;
	sphere1.color.g = 255;
	sphere1.color.b = 255; // CYAN
	sphere1.next = &sphere2;

	// SPHÈRE 2 : MOYENNE MAGENTA - Milieu
	sphere2.center.x = 10.0;
	sphere2.center.y = 8.0; // Au milieu en hauteur
	sphere2.center.z = 25.0;
	sphere2.diameter = 18.0;
	sphere2.color.r = 255;
	sphere2.color.g = 0;
	sphere2.color.b = 255; // MAGENTA
	sphere2.next = &sphere3;

	// SPHÈRE 3 : PETITE JAUNE - Premier plan
	sphere3.center.x = -5.0; // Très proche
	sphere3.center.y = 15.0; // En haut
	sphere3.center.z = 30.0;
	sphere3.diameter = 12.0;
	sphere3.color.r = 255;
	sphere3.color.g = 255;
	sphere3.color.b = 0; // JAUNE
	sphere3.next = NULL;

	// pl 0,0,0 0,1.0,0 255,0,225
	plane.point.x = 0.0;
	plane.point.y = 0.0;
	plane.point.z = 0.0;
	plane.normal.x = 0.0;
	plane.normal.y = 1.0;
	plane.normal.z = 0.0;
	plane.color.r = 255;
	plane.color.g = 0;
	plane.color.b = 225;
	plane.next = NULL;

	// cy 50.0,0.0,20.6 0,0,1.0 14.2 21.42 10,0,255
	cylinder.center.x = 50.0;
	cylinder.center.y = 0.0;
	cylinder.center.z = 20.6;
	cylinder.axis.x = 0.0;
	cylinder.axis.y = 0.0;
	cylinder.axis.z = 1.0;
	cylinder.diameter = 14.2;
	cylinder.height = 21.42;
	cylinder.color.r = 10;
	cylinder.color.g = 0;
	cylinder.color.b = 255;
	cylinder.next = NULL;

	// Remplir les structures principales
	env.ambient = &ambient;
	env.camera = &camera;
	env.light = &light;

	obj.spheres = &sphere1;
	obj.planes = &plane;
	obj.cylinders = &cylinder;

	// Appeler votre fonction de rendu
	init_miniRT(&env, &obj);

	return (0);
}