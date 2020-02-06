//
// Created by 李源 on 2020-02-06.
//

#ifndef MARCHINGCUBE_UTIL_H
#define MARCHINGCUBE_UTIL_H

#define GLFW_INCLUDE_GLCOREARB
#include <iostream>
#include <cstdlib>
#include <GLFW/glfw3.h>
#include <string>

GLFWwindow* init(std::string name,int width,int height) ;

GLuint createShader(const char* src, GLenum shaderType);
GLuint createShaderProgram(GLuint vertex, GLuint fragment);
GLuint createShaderProgram(GLuint vertex, GLuint geometry, GLuint fragment);
bool linkShader(GLuint program);
bool validateShader(GLuint program);









#endif //MARCHINGCUBE_UTIL_H
