//
// Created by 李源 on 2020-02-06.
//

#ifndef MARCHINGCUBE_OPENGL2_H
#define MARCHINGCUBE_OPENGL2_H
#include <GLUT/glut.h>
#include <string>
#include <iostream>
#include <vector>


#include "../data/data.h"
#include "../marchingcube/marchingcube.h"
#include <OpenGL/gl.h>
#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>


static std::string name ;
static GLfloat angle ;
static int refreshMills  = 15 ;

static std::vector<float> points;
static std::vector<GLuint> idxs;
static std::vector<float> normals;

void Opengl2(Data* data, Marchingcube* march,double *extent) ;
void initGL() ;
void  display() ;
void reshape(GLsizei width, GLsizei height) ;
void  timer(int value);
void run(int argc,char** argv);



#endif //MARCHINGCUBE_OPENGL2_H
