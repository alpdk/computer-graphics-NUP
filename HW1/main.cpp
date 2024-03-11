#include <GL/glut.h>

/* Initialize background color */

void initializeGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Setting black color as a background color
}

/* Display function */

void display2() {
    glClear(GL_COLOR_BUFFER_BIT);          // Clear the color buffer with current clearing color

    glBegin(GL_TRIANGLES);                 // Each set of 3 vertices form a triangle
    glColor3f(1.0f, 1.0f, 1.0f);  // White color for first vertical
    glVertex2f(0.0f, 0.0f);                 // Place of the first vertical
    glColor3f(1.0f, 1.0f, 1.0f);  // White color for second vertical
    glVertex2f(0.0f, 0.5f);                 // Place of the second vertical
    glColor3f(1.0f, 1.0f, 1.0f);  // White color for third vertical
    glVertex2f(0.5f, 0.0f);                 // Place of the third vertical
    glEnd();                                     // End setting verticals

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

