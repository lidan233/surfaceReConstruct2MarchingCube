cmake_minimum_required(VERSION 3.14)
project(marchingcube)

set(CMAKE_CXX_STANDARD 14)



set(GLEW_H /usr/local/Cellar/glew/2.1.0/include/GL)

set(GLFW_H /usr/local/Cellar/glfw/3.2.1/include/GLFW)

set(GLTOOLS_H /usr/local/include)

include_directories(${GLEW_H} ${GLFW_H} ${GLTOOLS_H})


link_directories(/usr/local/lib)

set(GLEW_LINK /usr/local/Cellar/glew/2.1.0/lib/libGLEW.2.1.dylib)

set(GLFW_LINK /usr/local/Cellar/glfw/3.2.1/lib/libglfw.3.dylib)


find_package(GLUT)


add_executable(marchingcube main.cpp data/Point.h data/Triangle.h data/Triangle.cpp data/data.h data/data.cpp
                marchingcube/marchingcube.h marchingcube/marchingcube.cpp
                gl/opengl2.h gl/opengl2.cpp )
#                opengl/opengl.h opengl/opengl.cpp
#                opengl/Material.h opengl/Material.cpp opengl/util.h opengl/util.cpp

link_libraries( ${GLEW_LINK} ${GLFW_LINK} )

target_link_libraries(marchingcube
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
        "-framework GLUT")
#        "-framework SDL")
