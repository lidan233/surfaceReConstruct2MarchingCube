#include <iostream>
#include "data/data.h"
#include "marchingcube/marchingcube.h"
#include <opengl/opengl.h>


#include "gl/opengl2.h"
int main(int argc,char** argv) {
    std::cout << "Hello, World!" << std::endl;

    Data data("");
    Marchingcube* march = new Marchingcube( data,500) ;
    march->run() ;
    march->computeNormals() ;
    march->writeFile("/Users/lidan/CLionProjects/marchingcube/data.obj");
//    Opengl* ol = new Opengl(&data,march,data.getExtent()) ;
//    ol->run() ;

    Opengl2(march->getData(),march,data.getExtent()) ;
    run(argc,argv);

    return 0;
}