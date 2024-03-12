#include <GL/glut.h>

/* Initialize background color */

void initializeGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Setting black color as a background color
}

/* Roate object by an angel */

void rotate(float angel) {
    glRotatef(angel, 0.0f, 0.0f, 1.0f);
}

/* Draw square function */

void draw_square(double x1, double y1, double sidelength) {
    double halfside = sidelength / 2;

    glColor3d(1, 1, 1);

    rotate(45);

    glScalef(1.1f, 1.1f, 1.0f);

    glBegin(GL_LINE_LOOP);

    glVertex2d(x1 + halfside, y1 + halfside);
    glVertex2d(x1 + halfside, y1 - halfside);
    glVertex2d(x1 - halfside, y1 - halfside);
    glVertex2d(x1 - halfside, y1 + halfside);

    glEnd();
}

/* Display square function */

void display_square() {
    glClear(GL_COLOR_BUFFER_BIT);          // Clear the color buffer with current clearing color

    draw_square(0, 0, 1);        // Draw square with center in 0, 0 with side 1

    glFlush();                                   // Render now
}

void draw_triangle() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-0.1f, -0.2f, 0.0f);
    glRotatef(60.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.1f, 0.2f, 0.0f);
    glRotatef(-60.0f, 0.0f, 1.0f, 0.0f);

    glBegin(GL_LINE_LOOP);

    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.1,0.3);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0,0.1);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.2,0.1);

    glEnd();
}

void display_triangle() {
    glClear(GL_COLOR_BUFFER_BIT);

    draw_triangle();

    glFlush();
}

/* Main function */

int main(int argc, char **argv) {
    glutInit(&argc, argv);               // Initialize GLUT
    glutCreateWindow("Some figures");         // Create window with the given title
    glutInitWindowSize(320, 320); // Set the window's width & height
    glutInitWindowPosition(50, 50);       // Install top-left corner of the winfow
    glutDisplayFunc(display_triangle);         // Register callback handler for window re-paint event
    initializeGL();                           // Our own OpenGL initialization
    glutMainLoop();                           // Enter the event-processing loop
    return 0;
}

