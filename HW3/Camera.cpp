//
// Created by alpdk on 5/31/24.
//

#include "Camera.h"

void Camera::set_camera() {
    gluLookAt(x, y, z,
              x + lx, y, z + lz,
              0.0f, 1.0f, 0.0f);
}

void Camera::rotate_camera(int rotation_side) {
    angle = angle + rotation_side * camera_rotation_angel;
    lx = sin(angle);
    lz = -cos(angle);
}

void Camera::move_camera(int move_direction) {
    x = x + move_direction * lx * fraction;
    z = z + move_direction * lz * fraction;
}
