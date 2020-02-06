//
// Created by 李源 on 2020-02-06.
//

#ifndef MARCHINGCUBE_MESH_H
#define MARCHINGCUBE_MESH_H


#include <glm/glm.hpp>
#include "util.h"


class Material {

public:
    Material();
    ~Material();

    bool load(const char* vertexSrc, const char* fragmentSrc);

    /**
     * Set a uniform to a certain value
     */
    bool setUniform(const char* name, const glm::mat4& m);
    /**
     * Use the underlying shader program
     */
    bool use();
    /**
     * Use the underlying shader program and bind
     * the textures
     */
    bool bind();
    void stopUsing();

    void setDiffuseTexture(GLuint texture);
private:
    GLuint program;
    GLuint diffuse;

};


#endif //MARCHINGCUBE_MESH_H
