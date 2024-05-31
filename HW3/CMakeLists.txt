cmake_minimum_required(VERSION 3.28)
project(HW3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lGL -lGLU -lglut")
set(CMAKE_CXX_STANDARD 17)

add_executable(HW3 main.cpp Camera.cpp LoadObject.cpp
        objload/objload.cpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
