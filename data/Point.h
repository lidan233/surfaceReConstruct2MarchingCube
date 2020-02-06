//
// Created by 李源 on 2020-02-05.
//

#ifndef MARCHINGCUBE_POINT_H
#define MARCHINGCUBE_POINT_H


class Point {
private:
    int _id ;
    double _x ;
    double _y ;
    double _z ;
    int value ;
    Point* xedgePoint = nullptr ;
    Point* yedgePoint = nullptr ;
    Point* zedgePoint = nullptr ;


public:
    Point(double x,double y,double z,int id):_x(x),_y(y),_z(z),_id(id){} ;
    Point(Point *another):_x(another->x()),_y(another->y()),_z(another->z()) {} ;
    Point(double* xyz,int id):_x(xyz[0]),_y(xyz[1]),_z(xyz[2]),_id(id){}


    double x() {return _x;}
    double y() {return _y;}
    double z() {return _z;}

    void setX(double x){ _x = x ;}
    void setY(double y){ _y = y ;}
    void setZ(double z){ _z = z ;}


    int id(){return _id ;}


    Point operator-(Point point)
    {
        return Point(_x-point.x(),_y-point.y(),_z-point.z(),-1) ;
    }


};


#endif //MARCHINGCUBE_POINT_H
