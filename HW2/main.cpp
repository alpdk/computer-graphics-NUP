#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define PI 3.14159265

/* Vector3D structure */
typedef struct {
    float x;
    float y;
    float z;
} Vector3D;

/* Finale triangle vertexes */
float triangle_vertex1[3] = {0, 0, 0};
float triangle_vertex2[3] = {0, 0, 0};
float triangle_vertex3[3] = {0, 0, 0};

/* Background color */
void initializeGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Setting black color as a background color
}

/* Initialize vertexes */
void initializeVertexes(float *vertexes1, float *vertexes2, float *vertexes3) {
    char c = 'x';

    printf("Vertex 1: \n");

    for (int i = 0; i < 3; i++) {
        printf("%c:", c + i);
        scanf("%f", &vertexes1[i]);
    }

    printf("Vertex 2: \n");

    for (int i = 0; i < 3; i++) {
        printf("%c:", c + i);
        scanf("%f", &vertexes2[i]);
    }

    printf("Vertex 3: \n");

    for (int i = 0; i < 3; i++) {
        printf("%c:", c + i);
        scanf("%f", &vertexes3[i]);
    }
}

/* Initialize transpose vector */
void initializeTranspose(Vector3D *transpose) {
    printf("Initialize transpose:\n");
    float *v;

    printf("x: ");
    scanf("%f", &transpose->x);

    printf("y: ");
    scanf("%f", &transpose->y);

    printf("z: ");
    scanf("%f", &transpose->z);
}

/* Create transpose matrix */
void translationMatrix(Vector3D *vector, float **matrix) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }

    // Set the translation values in the last column
    matrix[0][3] = vector->x;
    matrix[1][3] = vector->y;
    matrix[2][3] = vector->z;
}

/* Initialize rotation vector */
void initializeRotationVector(float *angel, Vector3D *rotation_vector) {
    printf("Initialize rotation:\n");

    printf("angel: ");
    scanf("%f", angel);

    printf("x: ");
    scanf("%f", &rotation_vector->x);

    printf("y: ");
    scanf("%f", &rotation_vector->y);

    printf("z: ");
    scanf("%f", &rotation_vector->z);
}

/* Normalize vector */
void normalize(Vector3D *p) {
    float w = sqrt(p->x * p->x + p->y * p->y + p->z * p->z);
    p->x /= w;
    p->y /= w;
    p->z /= w;
}

/* Calculate rotation matrix */
void rotationMatrix(Vector3D *axis, float angle, float **R) {
    float theta = angle * PI / 180.0;
    float cosTheta = cos(theta);
    float sinTheta = sin(theta);

    normalize(axis);

    R[0][0] = cosTheta + (1 - cosTheta) * axis->x * axis->x;
    R[0][1] = (1 - cosTheta) * axis->x * axis->y - sinTheta * axis->z;
    R[0][2] = (1 - cosTheta) * axis->x * axis->z + sinTheta * axis->y;

    R[1][0] = (1 - cosTheta) * axis->y * axis->x + sinTheta * axis->z;
    R[1][1] = cosTheta + (1 - cosTheta) * axis->y * axis->y;
    R[1][2] = (1 - cosTheta) * axis->y * axis->z - sinTheta * axis->x;

    R[2][0] = (1 - cosTheta) * axis->z * axis->x - sinTheta * axis->y;
    R[2][1] = (1 - cosTheta) * axis->z * axis->y + sinTheta * axis->x;
    R[2][2] = cosTheta + (1 - cosTheta) * axis->z * axis->z;
}

/* Multiply vector by matrix */
void multiplyVectorMatrices(const float *A, float **B, float *result) {
    for (int i = 0; i < 4; i++) {
        result[i] = 0;
        for (int k = 0; k < 4; k++) {
            result[i] += A[k] * B[k][i];
        }
    }
}

/* Get new vertex after applying changes */
void getNewVertex(float *vertex, float **transpose_matrix_1,
                  float **rotation_matrix, float **transpose_matrix_2,
                  float *new_vertex) {
    auto *tmp1 = (float *) malloc(4 * sizeof(float));
    auto *tmp2 = (float *) malloc(4 * sizeof(float));

    /* First transpose of vertex */
    multiplyVectorMatrices(vertex, transpose_matrix_1, tmp1);

    /* Rotation of vertex */
    multiplyVectorMatrices(tmp1, rotation_matrix, tmp2);

    /* Second transpose of vertex */
    multiplyVectorMatrices(tmp2, transpose_matrix_2, new_vertex);

    free(tmp1);
    free(tmp2);
}

/* Calculate new triangle */
void newTriangle() {
    float *vertexes1;
    float *vertexes2;
    float *vertexes3;

    /* Allocate memory for vertexes */
    vertexes1 = (float *) malloc(4 * sizeof(float));
    vertexes2 = (float *) malloc(4 * sizeof(float));
    vertexes3 = (float *) malloc(4 * sizeof(float));

    /* Initialize vertexes */
    initializeVertexes(vertexes1, vertexes2, vertexes3);

    /* Allocate memory for transpose vector and transpose matrix */
    auto *transpose1 = new Vector3D;
    auto **transpose_matrix_1 = (float **) malloc(sizeof(float *) * 4);
    for (int i = 0; i < 4; ++i) {
        transpose_matrix_1[i] = (float *) malloc(sizeof(float) * 4);
    }

    /* Initialize transpose vector and calculate transpose matrix */
    initializeTranspose(transpose1);
    translationMatrix(transpose1, transpose_matrix_1);
    free(transpose1);

    /* Allocate memory for rotation vector and rotation matrix */
    float angel;
    auto *rotation_vector = new Vector3D;
    auto **rotation_matrix = (float **) malloc(sizeof(float *) * 4);
    for (int i = 0; i < 4; ++i) {
        rotation_matrix[i] = (float *) malloc(sizeof(float) * 4);
    }

    /* Initialize transpose rotation and calculate rotation matrix */
    initializeRotationVector(&angel, rotation_vector);
    rotationMatrix(rotation_vector, angel, rotation_matrix);
    free(rotation_vector);

    /* Allocate memory for transpose vector and transpose matrix */
    auto *transpose2 = new Vector3D;
    auto **transpose_matrix_2 = (float **) malloc(sizeof(float *) * 4);
    for (int i = 0; i < 4; ++i) {
        transpose_matrix_2[i] = (float *) malloc(sizeof(float) * 4);
    }

    /* Initialize transpose vector and calculate transpose matrix */
    initializeTranspose(transpose2);
    translationMatrix(transpose2, transpose_matrix_2);
    free(transpose2);

    /* Allocate memory for new vertexes */
    auto *new_vertexes1 = (float *) malloc(4 * sizeof(float));
    auto *new_vertexes2 = (float *) malloc(4 * sizeof(float));
    auto *new_vertexes3 = (float *) malloc(4 * sizeof(float));

    /* Calculate new vertexes */
    getNewVertex(vertexes1, transpose_matrix_1, rotation_matrix, transpose_matrix_2, new_vertexes1);
    getNewVertex(vertexes2, transpose_matrix_1, rotation_matrix, transpose_matrix_2, new_vertexes2);
    getNewVertex(vertexes3, transpose_matrix_1, rotation_matrix, transpose_matrix_2, new_vertexes3);

    free(vertexes1);
    free(vertexes2);
    free(vertexes3);
    free(transpose_matrix_1);
    free(rotation_matrix);
    free(transpose_matrix_2);

    /* Save new vertexes */
    triangle_vertex1[0] = new_vertexes1[0];
    triangle_vertex1[1] = new_vertexes1[1];
    triangle_vertex1[2] = new_vertexes1[2];

    triangle_vertex2[0] = new_vertexes2[0];
    triangle_vertex2[1] = new_vertexes2[1];
    triangle_vertex2[2] = new_vertexes2[2];

    triangle_vertex3[0] = new_vertexes3[0];
    triangle_vertex3[1] = new_vertexes3[1];
    triangle_vertex3[2] = new_vertexes3[2];

    free(new_vertexes1);
    free(new_vertexes2);
    free(new_vertexes3);
}

void draw_triangle() {
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glBegin(GL_LINE_LOOP);

    // glColor3f(1.0f, 1.0f, 1.0f);
    //glColor3f(0.0f, 1.0f, 0.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(triangle_vertex1[0], triangle_vertex1[1], triangle_vertex1[2]);
    //glColor3f(1.0f, 1.0f, 1.0f);
    //glColor3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(triangle_vertex2[0], triangle_vertex2[1], triangle_vertex3[2]);
    //glColor3f(1.0f, 1.0f, 1.0f);
    //glColor3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(triangle_vertex3[0], triangle_vertex3[1], triangle_vertex2[2]);

    glEnd();

    glFlush();
}

/* Main function */

int main(int argc, char **argv) {
    newTriangle();
    glutInit(&argc, argv);               // Initialize GLUT
    glutCreateWindow("Some figures");         // Create window with the given title
    glutInitWindowSize(320, 320); // Set the window's width & height
    glutInitWindowPosition(50, 50);       // Install top-left corner of the winfow
    glutDisplayFunc(draw_triangle);         // Register callback handler for window re-paint event
    initializeGL();                           // Our own OpenGL initialization
    glutMainLoop();                           // Enter the event-processing loop*/
    return 0;
}

