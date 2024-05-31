#define OBJL_CONSOLE_OUTPUT
#define STB_IMAGE_IMPLEMENTATION

#include <GL/glut.h>
#include <stdexcept>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <utility>

#include "OBJ_Loader.h"
#include "stb/stb_image.h"
//
#define PATH_TO_PROJ "/home/alpdk/gitRepos/computer-graphics-NUP/HW3/"
#define PI 3.14159265

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

    void set_camera() {
        gluLookAt(x, y, z,
                  x + lx, y, z + lz,
                  0.0f, 1.0f, 0.0f);
    }

    void rotate_camera(int rotation_side) {
        angle = angle + rotation_side * camera_rotation_angel;
        lx = sin(angle);
        lz = -cos(angle);
    }

    void move_camera(int move_direction) {
        x = x + move_direction * lx * fraction;
        z = z + move_direction * lz * fraction;
    }
};

class Planet {
private:
    int place;
    float some_val = 0.0;

    float rotate_meridian;
    std::vector<float> rotate_meridian_vec;

    float rotate_meridian_speed;
    float rotate_across_sun_speed;

    float scale;

    std::string path_to_obj_dir;

    std::vector<GLuint> textures_ids;
    std::vector<objl::Mesh> meshes;

    void rotating_meridian() {
        glRotatef(rotate_meridian, rotate_meridian_vec[0],
                  rotate_meridian_vec[1],
                  rotate_meridian_vec[2]);
    }

    void rotating_across_meridian(float t) {
        glRotatef(rotate_meridian_speed * t, 0, 1, 0);
    }

    void translating_and_rotating_across_the_sun(float t) {
        float r = 2.0f * (float) place;
        float u = 3 * rotate_across_sun_speed * t;
        glTranslatef(r, 0, r);
        glRotatef(rotate_across_sun_speed, 0, 1, 0);
    }

public:
    Planet(std::string folder_name,
           int place,
           float rotate_meridian = 0,
           float rotate_meridian_speed = 10,
           std::vector<float> rotate_meridian_vec = {0, 0, 0},
           float scale = 1000) : place(place),
                                 rotate_meridian(rotate_meridian),
                                 rotate_meridian_speed(rotate_meridian_speed),
                                 rotate_meridian_vec(std::move(rotate_meridian_vec)),
                                 scale(scale) {
        if (place != 0) {
            rotate_across_sun_speed = 2 * PI / (10.0f * (float) place * 0.65f);
        } else {
            rotate_across_sun_speed = 0;
        }

        std::stringstream path_to_proj;
        path_to_proj << PATH_TO_PROJ;

        std::stringstream path_to_solar_system;

        path_to_solar_system << path_to_proj.str() << "solar_system/";

        std::stringstream path_to_planet_dir;

        path_to_planet_dir << path_to_solar_system.str() << folder_name << "/";

        path_to_obj_dir = path_to_planet_dir.str();

        objl::Loader loader;
        std::string obj_path = path_to_planet_dir.str() + folder_name + ".obj";

        loader.LoadFile(obj_path);

        for (int i = 0; i < loader.LoadedMeshes.size(); i++) {
            meshes.push_back(loader.LoadedMeshes[i]);
        }
    }

    void setup_textures() {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClearDepth(1.0f);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        for (int i = 0; i < meshes.size(); i++) {
            std::string path_to_image = path_to_obj_dir + meshes[i].MeshMaterial.map_Ka;

            int width, height, channels;

            unsigned char *img = stbi_load(path_to_image.c_str(), &width, &height, &channels, 0);

            GLuint tmp;

            glGenTextures(1, &tmp);
            glBindTexture(GL_TEXTURE_2D, tmp);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
            glBindTexture(GL_TEXTURE_2D, 0);

            textures_ids.push_back(std::move(tmp));

            stbi_image_free(img);
        }
    }

    void draw(float t) {
        glPushMatrix();

        rotating_across_meridian(t);

        translating_and_rotating_across_the_sun(t);

        rotating_meridian();

        glScalef(1.0f / scale, 1.0f / scale, 1.0f / scale);

        for (int i = 0; i < meshes.size(); i++) {
            glBindTexture(GL_TEXTURE_2D, textures_ids[i]);

            for (int j = 0; j < meshes[i].Indices.size() - 3; j += 3) {
                std::vector<int> vertexes = {};

                vertexes.push_back(meshes[i].Indices[j]);
                vertexes.push_back(meshes[i].Indices[j + 1]);
                vertexes.push_back(meshes[i].Indices[j + 2]);

                glBegin(GL_TRIANGLES);

                for (const auto &k: vertexes) {
                    glTexCoord2f(meshes[i].Vertices[k].TextureCoordinate.X,
                                 meshes[i].Vertices[k].TextureCoordinate.Y);

                    glVertex3f(meshes[i].Vertices[k].Position.X,
                               meshes[i].Vertices[k].Position.Y,
                               meshes[i].Vertices[k].Position.Z);
                }

                glEnd();
            }

            glBindTexture(GL_TEXTURE_2D, 0);
        }

        some_val += 0.1;

        glPopMatrix();
    }
};

class SolarSystem {
private:
    std::vector<Planet> planets;

    std::vector<std::string> names_of_planet = {
            "sun",
            "mercury",
            "venus",
            "earth",
            "mars",
            "jupiter",
            "saturn",
            "uranus",
            "neptune"
    };

    std::vector<float> planets_rotate_meridian = {
            90, 90, 90,
            90, 90, 90,
            90, 90, 90,
    };
    std::vector<float> planets_rotate_meridian_speed = {
            20, 18, 16,
            14, 12, 10,
            8, 6, 4
    };
    std::vector<std::vector<float>> planets_rotate_meridian_vec = {
            {1, 0, 0},
            {1, 0, 0},
            {1, 0, 0},
            {1, 0, 0},
            {1, 0, 0},
            {1, 0, 0},
            {1, 0, 0},
            {1, 0, 0},
            {1, 0, 0},
    };
    std::vector<float> planets_scale = {
            1000.0f, 1000.0f, 1000.0f,
            1000.0f, 1000.0f, 1000.0f,
            1000.0f, 1000.0f, 1000.0f,
    };
public:
    SolarSystem() {
        for (int i = 0; i < 9; i++) {
            planets.push_back(Planet(names_of_planet[i],
                                     i,
                                     planets_rotate_meridian[i],
                                     planets_rotate_meridian_speed[i],
                                     planets_rotate_meridian_vec[i],
                                     planets_scale[i]));
        }
    }

    void setup_textures() {
        for (auto& i : planets) {
            i.setup_textures();
        }
    }

    void draw(float t) {
        for (auto& i : planets) {
            i.draw(t);
        }
    }
};


Camera camera;

SolarSystem solarSystem = SolarSystem();

void changeSize(int w, int h) {

// Prevent a divide by zero, when window is too short
// (you cant make a window of zero width).
    if (h == 0)
        h = 1;
    float ratio = w * 1.0 / h;

// Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);

// Reset Matrix
    glLoadIdentity();

// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

// Set the correct perspective.
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);

// Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}

void renderScene(void) {

    int mills = glutGet(GLUT_ELAPSED_TIME);
    float t = (float) mills / 1000.0f;

// Clear Color and Depth Buffers

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

// Reset transformations
    glLoadIdentity();
// Set the camera
    camera.set_camera();

// Draw planet
    glTranslatef(0.0, 1.0, 0.0);

    solarSystem.draw(t);

    glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) {

    if (key == 27)
        exit(0);
}

void processSpecialKeys(int key, int xx, int yy) {

    switch (key) {
        case GLUT_KEY_LEFT :
            camera.rotate_camera(-1);
            break;
        case GLUT_KEY_RIGHT :
            camera.rotate_camera(1);
            break;
        case GLUT_KEY_UP :
            camera.move_camera(1);
            break;
        case GLUT_KEY_DOWN :
            camera.move_camera(-1);
            break;
    }
}

void init() {
    solarSystem.setup_textures();
}

int main(int argc, char **argv) {

// init GLUT and create window

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(320, 320);
    glutCreateWindow("Lighthouse3D - GLUT Tutorial");

    init();

// register callbacks
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);

// OpenGL init
    glEnable(GL_DEPTH_TEST);

// enter GLUT event processing cycle
    glutMainLoop();

    return 0;
}