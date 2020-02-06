//
// Created by 李源 on 2020-02-05.
//

#include "Triangle.h"
#include <math.h>

inline double Det3x3(double* col_0, double* col_1, double* col_2)
{
    // Gets the determinant of a 3x3 matrix, where the arguments ae 3-long column vectors

    // Names all the objects in the matrix for my convenience
    double a = col_0[0];
    double b = col_1[0];
    double c = col_2[0];
    double d = col_0[1];
    double e = col_1[1];
    double f = col_2[1];
    double g = col_0[2];
    double h = col_1[2];
    double i = col_2[2];

    // Return the alternating sum of the 2x2 determinants of the coproducts
    double det = a * (e * i - f * h) - b * (d * i - f * g) + c * (d * h - e * g);
    return det;
}




//判定abc是否是逆时针 也就是三阶行列式是否大于0
inline bool CCW(Point* a, Point* b , Point* c )
{
//   Eigen::Matrix3d matrix ;
//   matrix<< a->x(),b->x(),c->x() ,
//            a->y(),b->y(),c->y(),
//            1,1,1;
//   return matrix.determinant()>0 ;

    Point first = *b-*a;
    Point second =*c-*a ;
    double m[3][3] = { { first.x(),first.y(),first.z() }, { second.x(), second.y(), second.z() }, { 1, 1, 1 } };
    return Det3x3(m[0], m[1], m[2]) > 0;
}


bool Triangle::isClock(Data *data)
{
    //判断是不是逆时针
    return CCW(data->getPoint(_idx[0]),data->getPoint(_idx[1]),data->getPoint(_idx[1]));
}

bool Triangle::filter(Data* data)
{
    if(!isClock(data))
    {
        changeClock() ;
    }
}

std::string Triangle::to_string()
{
    return std::to_string(_idx[0]+1)+" "+std::to_string(_idx[1]+1)+" "+std::to_string(_idx[2]+1) ;
}

inline void Normalize3(double *v)
{
    double len = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    v[0] /= len;
    v[1] /= len;
    v[2] /= len;
}

double* Triangle::getNormal(int i,Data* data)
{
    Point first = *(data->getPoint(_idx[(i+1)%3])) - *(data->getPoint(_idx[i])) ;
    Point second = *(data->getPoint(_idx[(i+2)%3])) - *(data->getPoint(_idx[i])) ;

    double* result = new double[3] ;


    result[0] = first.y()*second.z() - first.z()*second.y() ;
    result[1] = first.z()*second.x() - first.x()*second.z() ;
    result[3] = first.x()*second.y() - first.y()*second.x() ;
    Normalize3(result) ;

    return result ;
}






