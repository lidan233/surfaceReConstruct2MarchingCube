//
// Created by 李源 on 2020-02-05.
//

#ifndef MARCHINGCUBE_TRIANGLE_H
#define MARCHINGCUBE_TRIANGLE_H
#include <vector>
#include <string>
#include "Point.h"
#include "data.h"

class Triangle {
private:
    int *_idx ;
public:

    Triangle(int idx[3]):_idx(idx){}


    bool changeClock() {int temp = _idx[0];_idx[0]=_idx[1];_idx[1] = temp;}
    bool isClock(Data *data);
    bool filter(Data *data);
    int getIdx(int i) {return _idx[i] ;}

    double* getNormal(int i,Data* data);
    std::string to_string();


};


#endif //MARCHINGCUBE_TRIANGLE_H
