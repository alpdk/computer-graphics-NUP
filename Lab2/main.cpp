#include <GL/glut.h>
#include <math.h>
float camera_position[3] = {0.10f, 0.10f, 0.10f};
float camera_orientation[3] = {0.0f, 0.0f, 0.0f};

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camera_position[0], camera_position[1], camera_position[2],
              camera_orientation[0], camera_orientation[1], camera_orientation[2],
              0.0f, 1.0f, 0.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    GLUquadricObj* quadric = gluNewQuadric();
    gluCylinder(quadric, 0.05, 0.05, 0.1, 3, 3);
    gluDeleteQuadric(quadric);
    glutSwapBuffers();
}
void keyboard(unsigned char key, int x, int y)
{
    float step = 0.1f;
    switch (key) {
        case 'w': // move forward
            camera_position[2] -= step;
            break;
        case 's': // move backward
            camera_position[2] += step;
            break;
        case 'a': // strafe left
            camera_position[0] -= step;
            break;
        case 'd': // strafe right
            camera_position[0] += step;
            break;
    }
    glutPostRedisplay();
}

void special(int key, int x, int y)
{
    float angle_step = 0.1f;
    float radius = sqrt(pow(camera_position[0], 2) + pow(camera_position[2], 2));
    float angle = atan2(camera_position[0], camera_position[2]);
    switch (key) {
        case GLUT_KEY_UP: // pitch up
            camera_position[1] -= 0.1f;
            break;
        case GLUT_KEY_DOWN: // pitch down
            camera_position[1] += 0.1f;
            break;
        case GLUT_KEY_LEFT: // yaw left
            angle -= angle_step;
            camera_position[0] = radius * sin(angle);
            camera_position[2] = radius * cos(angle);
            break;
        case GLUT_KEY_RIGHT: // yaw right
            angle += angle_step;
            camera_position[0] = radius * sin(angle);
            camera_position[2] = radius * cos(angle);
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Camera Control");
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutMainLoop();
    return 0;
}