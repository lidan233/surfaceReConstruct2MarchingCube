//
// Created by 李源 on 2020-02-06.
//

#include "opengl2.h"



void Opengl2(Data* data, Marchingcube* march,double *extent)
{
    angle = 0.05 ;
    name = "marching cube mesh ";
    std::cout<<"extent is "<<std::to_string(extent[0])<<" "
                            <<std::to_string(extent[1])<<" "
                            <<std::to_string(extent[2])<<" "
                            <<std::to_string(extent[3])<<" "
                            <<std::to_string(extent[4])<<" "
                            <<std::to_string(extent[5])<<std::endl ;
    for(int i  =0 ;i< data->getPointSize();i++)
    {
        Point* temp = data->getPoint(i) ;
        points.push_back(temp->x()) ;
        points.push_back(temp->y()) ;
        points.push_back(temp->z()) ;

//        points.push_back((temp->x()-extent[0])/(extent[1]-extent[0])) ;
//        points.push_back((temp->y()-extent[2])/(extent[3]-extent[2]));
//        points.push_back((temp->z()-extent[4])/(extent[5]-extent[4]));
//        std::cout<<std::to_string((temp->x()-extent[0])/(extent[1]-extent[0]))<<" "
//        <<std::to_string((temp->y()-extent[2])/(extent[3]-extent[2]))<<" "
//        <<std::to_string((temp->z()-extent[4])/(extent[5]-extent[4]))<<std::endl ;
//
//        points.push_back(1.0f); // r
//        points.push_back(1.0f); // g
//        points.push_back(1.0f); // b

        double* normal = march->getVertexNormalOf(i) ;
        normals.push_back(normal[0]) ;
        normals.push_back(normal[1]) ;
        normals.push_back(normal[2]) ;
    }

    for(int i =0 ;i< march->getTriangleSize();i++)
    {
        idxs.push_back(march->getTriangle(i)->getIdx(0)) ;
        idxs.push_back(march->getTriangle(i)->getIdx(1)) ;
        idxs.push_back(march->getTriangle(i)->getIdx(2)) ;
    }


}

void initGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClearDepth(1.0f);                   // Set background depth to farthest
    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
    glShadeModel(GL_SMOOTH);   // Enable smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix


    glEnable(GL_LIGHTING);
    glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 0);


    GLfloat  light_ambient[] = {0,0,0,1};
    GLfloat  light_diffuse[] = {1,1,1,1};
    GLfloat  light_specular[] = {1,1,1,1};
    GLfloat  light_positon[] = {0,0,1,1};

    glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient) ;
    glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diffuse) ;
    glLightfv(GL_LIGHT0,GL_SPECULAR,light_specular) ;
    glLightfv(GL_LIGHT0,GL_POSITION,light_positon);
    glEnable(GL_LIGHT0) ;


    // Render a color-cube consisting of 6 quads with different colors
    glLoadIdentity();                 // Reset the model-view matrix
    glTranslatef(1.5f, 0.0f, -7.0f);  // Move right and into the screen
    glRotatef(angle, 1.0f, 1.0f, 1.0f);  // Rotate about (1,1,1)-axis [NEW]

    glBegin(GL_TRIANGLES);
    for(int i  = 0; i< idxs.size();i+=3)
    {
        glColor3f(0.0f,0.0f,1.0f) ;
        glNormal3f(normals[idxs[i]*3],normals[idxs[i]*3+1],normals[idxs[i]*3+2]);
        glVertex3f(points[idxs[i]*3],points[idxs[i]*3+1],points[idxs[i]*3+2]) ;

        glColor3f(0.0f,0.0f,1.0f) ;
        glNormal3f(normals[idxs[i+1]*3],normals[idxs[i+1]*3+1],normals[idxs[i+1]*3+2]);
        glVertex3f(points[idxs[i+1]*3],points[idxs[i+1]*3+1],points[idxs[i+1]*3+2]) ;
        glColor3f(0.0f,0.0f,1.0f) ;
        glNormal3f(normals[idxs[i+2]*3],normals[idxs[i+2]*3+1],normals[idxs[i+2]*3+2]);
        glVertex3f(points[idxs[i+2]*3],points[idxs[i+2]*3+1],points[idxs[i+2]*3+2]) ;
    }
    glEnd();

    glutSwapBuffers();

    angle+=0.15;
}

void timer(int value) {
    glutPostRedisplay();      // Post re-paint request to activate display()
    glutTimerFunc(refreshMills, timer, 0); // next timer call milliseconds later
}

void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
    // Compute aspect ratio of the new window
    if (height == 0) height = 1;                // To prevent divide by 0
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);

    // Set the aspect ratio of the clipping volume to match the viewport
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();             // Reset
    // Enable perspective projection with fovy, aspect, zNear and zFar
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);

    gluLookAt(0.0,0.0,1,  0.0,0.0,0.0,  0.0,1.0,0.0);


}

void run(int argc,char** argv)
{

    glutInit(&argc,argv);            // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
    glutInitWindowSize(640, 480);   // Set the window's initial width & height
    glutInitWindowPosition(0, 0); // Position the window's initial top-left corner
    glutCreateWindow(name.c_str());          // Create window with the given title
    glutDisplayFunc(display);       // Register callback handler for window re-paint event
    glutReshapeFunc(reshape);       // Register callback handler for window re-size event
    initGL();                       // Our own OpenGL initialization
    glutTimerFunc(0, timer, 0);     // First timer call immediately [NEW]
    glutMainLoop();                 // Enter the infinite event-processing loop

}



