#include "miniRT.h"

int main(void)
{
    t_environment   env;
    t_object        obj;
    t_ambient       ambient;
    t_camera        camera;
    t_light         light;
    
    static t_cylinder cylinder;
    static t_sphere sphere1;
    static t_sphere sphere2;
    static t_sphere sphere3;
    t_plane         plane;

    // ========== AMBIENT LIGHT ==========
    ambient.ratio = 0.25;
    ambient.color.r = 255;
    ambient.color.g = 255;
    ambient.color.b = 255;

    // ========== CAMERA (VUE DE CÔTÉ) ==========
    camera.position.x = -35.0;
    camera.position.y = 20.0;
    camera.position.z = -25.0;
    camera.orientation.x = 0.6;
    camera.orientation.y = -0.4;
    camera.orientation.z = 0.5;
    camera.fov = 75;
    camera.samples_per_pixel = QUALITY;

    // ========== LIGHT ==========
    light.position.x = -20.0;
    light.position.y = 13.0;
    light.position.z = 5.0;
    light.brightness = 0.7;
    light.color.r = 255;
    light.color.g = 255;
    light.color.b = 255;

    // ========== PLANE (SOL) ==========
    plane.point.x = 0.0;
    plane.point.y = -10.0;
    plane.point.z = 0.0;
    plane.normal.x = 0.0;
    plane.normal.y = 1.0;
    plane.normal.z = 0.0;
    plane.color.r = 70;
    plane.color.g = 70;
    plane.color.b = 70;
    plane.next = NULL;

    // ========== CYLINDRE (COLONNE VERTE) ==========
    cylinder.center.x = 0.0;
    cylinder.center.y = 2.0;      // Un peu au-dessus du sol
    cylinder.center.z = 5.0;
    cylinder.axis.x = 0.0;
    cylinder.axis.y = 1.0;        // Vertical
    cylinder.axis.z = 0.0;
    cylinder.diameter = 6.0;
    cylinder.height = 20.0;
    cylinder.color.r = 50;
    cylinder.color.g = 220;
    cylinder.color.b = 50;
    cylinder.next = NULL;

    // ========== SPHERE 1 (ROUGE - devant à gauche) ==========
    sphere1.center.x = -12.0;
    sphere1.center.y = -2.0;
    sphere1.center.z = 5.0;
    sphere1.diameter = 8.0;
    sphere1.color.r = 255;
    sphere1.color.g = 50;
    sphere1.color.b = 50;
    sphere1.next = &sphere2;

    // ========== SPHERE 2 (BLEUE - devant à droite) ==========
    sphere2.center.x = 12.0;
    sphere2.center.y = -2.0;
    sphere2.center.z = 12.0;
    sphere2.diameter = 8.0;
    sphere2.color.r = 50;
    sphere2.color.g = 100;
    sphere2.color.b = 255;
    sphere2.next = &sphere3;

    // ========== SPHERE 3 (JAUNE - au sommet) ==========
    sphere3.center.x = 0.0;
    sphere3.center.y = 13.0;      // Juste au-dessus du cylindre
    sphere3.center.z = 5.0;
    sphere3.diameter = 7.0;
    sphere3.color.r = 255;
    sphere3.color.g = 255;
    sphere3.color.b = 50;
    sphere3.next = NULL;

    // ========== ASSEMBLAGE ==========
    env.ambient = &ambient;
    env.camera = &camera;
    env.light = &light;

    obj.spheres = &sphere1;
    obj.planes = &plane;
    obj.cylinders = &cylinder;

    init_miniRT(&env, &obj);

    return (0);
}