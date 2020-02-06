//
// Created by 李源 on 2020-02-05.
//

#ifndef MARCHINGCUBE_OPENGL_H
#define MARCHINGCUBE_OPENGL_H


#include "../data/data.h"
#include "../marchingcube/marchingcube.h"
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include "util.h"
#include "Material.h"

class Opengl {
private:
    std::vector<float> positions ;
    std::vector<int> indexs ;

    const char* vertex = "#version 330 core\n"
                             "layout(location=0) in vec3 position;"          // Vertex position (x, y, z)
                             "layout(location=1) in vec3 color;"             // Vertex color (r, g, b)
                             //                          "layout(location=2) in vec2 texcoord;"          // Texture coordinate (u, v)
                             "uniform mat4 model;"
                             "uniform mat4 view;"
                             "uniform mat4 projection;"
                             "out vec3 fColor;"                              // Vertex shader has to pass color to fragment shader
                             //                          "out vec2 fTexcoord;"                           // Pass to fragment shader
                             "void main()"
                             "{"
                             "    fColor = color;"                           // Pass color to fragment shader
                             //                          "    fTexcoord = texcoord;"                     // Pass texcoord to fragment shader
                             "    gl_Position = projection * view * model * vec4(position, 1.0);"     // Place vertex at (x, y, z, 1) and then transform it according to the projection, view and model matrices
                             "}";

    const char* fragment = "#version 330 core\n"
                               "in vec3 fColor;"                              // From the vertex shader
                               //                           "in vec2 fTexcoord;"                           // From the vertex shader
                               //                           "uniform sampler2D diffuse;"                       // The texture
                               "out vec4 outputColor;"                        // The color of the resulting fragment
                               "void main()"
                               "{"
                               //                           "    outputColor = texture(diffuse, fTexcoord)"   // Color using the color and texutre
                               //                           "                  * vec4(fColor, 1.0);"
                               "    outputColor = vec4(fColor, 1.0);"
                               "}";


    std::vector<float> points;
    std::vector<GLuint> idxs;

    int numIndices;
    glm::vec3 position, scale, angle;
    GLuint vao;

public:
    Opengl(Data* data, Marchingcube* march,double *extent);
    ~Opengl() ;

    void setPosition(float x, float y, float z);
    void setScale(float x, float y, float z);
    void setAngle(float x, float y, float z);

    void render();

    glm::mat4 getModelMatrix();

    void run() ;




};


#endif //MARCHINGCUBE_OPENGL_H
