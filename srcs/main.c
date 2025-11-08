#include "miniRT.h"

int main(void)
{
    t_environment env;
    t_object obj;
    t_ambient ambient;
    t_camera camera;
    t_light light;
    t_sphere sphere;
    t_plane plane;
    t_cylinder cylinder;

    // A 0.2 255,255,255
    ambient.ratio = 0.2;
    ambient.color.r = 255;
    ambient.color.g = 255;
    ambient.color.b = 255;

    // C -50,0,20 0,0,1 70
    camera.position.x = -50.0;
    camera.position.y = 0.0;
    camera.position.z = 20.0;
    camera.orientation.x = 0.0;
    camera.orientation.y = 0.0;
    camera.orientation.z = 1.0;
    camera.fov = 70;

    // L -40,0,30 0.7 255,255,255
    light.position.x = -40.0;
    light.position.y = 0.0;
    light.position.z = 30.0;
    light.brightness = 0.7;
    light.color.r = 255;
    light.color.g = 255;
    light.color.b = 255;

    // sp 0,0,20 20 255,0,0
    sphere.center.x = 0.0;
    sphere.center.y = 0.0;
    sphere.center.z = 20.0;
    sphere.diameter = 20.0;
    sphere.color.r = 255;
    sphere.color.g = 0;
    sphere.color.b = 0;
    sphere.next = NULL;

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

    obj.spheres = &sphere;
    obj.planes = &plane;
    obj.cylinders = &cylinder;

    // Appeler votre fonction de rendu
    init_miniRT(&env, &obj);

    return (0);
}
