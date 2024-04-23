#include <GL/glut.h>

void display() {
    float g_RotateX = 0.0f;
    float g_RotationSpeed = 0.1f;

    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
//    glTranslatef(0.0f, 0.0f, -0.5f);
    gluLookAt(0.075, 0.05, 0.1, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glColor3f(0.0f, 0.0f, 1.0f);
    glutSolidCube(0.2f);

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Blue Cube");
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}