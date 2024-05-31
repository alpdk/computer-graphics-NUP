#include <GL/glut.h>

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 1.0f);
    glLoadIdentity();
    glTranslatef(0.1f, 0.2f, 0.0f);
    glScalef(1.0f, 2.0f, 1.0f);
    glTranslatef(-0.1f, -0.2f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(0.1f, 0.2f);
    glVertex2f(0.2f, 0.2f);
    glVertex2f(0.2f, 0.3f);
    glVertex2f(0.1f, 0.3f);
    glEnd();
    glFlush();
}

void init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutCreateWindow("Modified Shape");
    glutInitWindowSize(640, 480);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-640)/2, (glutGet(GLUT_SCREEN_HEIGHT)-480)/2);
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}