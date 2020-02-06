//
// Created by 李源 on 2020-02-05.
//



#ifndef MARCHINGCUBE_DATA_H
#define MARCHINGCUBE_DATA_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "Point.h"

class Data {
private:
    int image_x ;
    int image_y ;
    int image_z ;

    float space_x ;
    float space_y ;
    float space_z ;

    float origin_x ;
    float origin_y ;
    float origin_z ;

    int numbers ;

    int* values ;
    double* extent ;

    int* lastpointsEdgeIds ;
    std::vector<Point*> lastPoints ;


public:
    Data(std::string file) ;
    int getVertexVal(int x,int y,int z);
    double* getVertexLoc(int x,int y,int z);

    int getPointSize(){return lastPoints.size() ;}
    Point* getPoint(int i){return lastPoints[i] ;}

    int getIdx(int x,int y,int z);

    void normalPoints();

    Point* getVertexXedgeP(int x,int y,int z,int thre) ;
    Point* getVertexYedgeP(int x,int y,int z,int thre) ;
    Point* getVertexZedgeP(int x,int y,int z,int thre) ;

    double* getExtent(){return extent ;}
    void SetExtent(Point* point) ;

    int size_x() {return image_x ;}
    int size_y() {return image_y ;}
    int size_z() {return image_z ;}






};


#endif //MARCHINGCUBE_DATA_H
