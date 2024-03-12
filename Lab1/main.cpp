#include <GL/glut.h>

/* Initialize background color */

void initializeGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Setting black color as a background color
}

void rotate(float angel) {
    glRotatef(angel, 0.0f, 0.0f, 1.0f);
}

/* Draw square function */

void drawSquare(double x1, double y1, double sidelength) {
    double halfside = sidelength / 2;

    rotate(45);

    glColor3d(1, 1, 1);
    glBegin(GL_LINE_LOOP);

    glVertex2d(x1 + halfside, y1 + halfside);
    glVertex2d(x1 + halfside, y1 - halfside);
    glVertex2d(x1 - halfside, y1 - halfside);
    glVertex2d(x1 - halfside, y1 + halfside);

    glEnd();
}

/* Display function */

void display2() {
    glClear(GL_COLOR_BUFFER_BIT);          // Clear the color buffer with current clearing color

    drawSquare(0, 0, 1);        // Draw square with center in 0, 0 with side 1

    glFlush();                                   // Render now
}

/* Main function */

int main(int argc, char **argv) {
    glutInit(&argc, argv);               // Initialize GLUT
    glutCreateWindow("Triangle");         // Create window with the given title
    glutInitWindowSize(320, 320); // Set the window's width & height
    glutInitWindowPosition(50, 50);       // Install top-left corner of the winfow
    glutDisplayFunc(display2);         // Register callback handler for window re-paint event
    initializeGL();                           // Our own OpenGL initialization
    glutMainLoop();                           // Enter the event-processing loop
    return 0;
}

