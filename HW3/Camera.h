#include <GL/glut.h>
#include <cmath>

class Camera {
private:
    // actual vector representing the camera's direction
    float lx = 0.0f, lz = -1.0f;

    // XZ position of the camera
    float x = 0.0f, y = 1.0f, z = 5.0f;

    // angle for rotating triangle
    float angle = 0.0f;

    // value for camera rotation
    float camera_rotation_angel = 0.05f;

    // value for camera step
    float fraction = 0.5f;

public:

    void set_camera();

    void rotate_camera(int rotation_side);

    void move_camera(int move_direction);
};


