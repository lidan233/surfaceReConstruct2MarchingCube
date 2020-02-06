//
// Created by 李源 on 2020-02-05.
//

#include "data.h"
#include <limits>

inline void split(const std::string& s,std::vector<std::string>& sv,const char* delim = " ") {
    sv.clear();                                 // 1.
    char* buffer = new char[s.size() + 1];      // 2.
    buffer[s.size()] = '\0';
    std::copy(s.begin(), s.end(), buffer);      // 3.
    char* p = std::strtok(buffer, delim);       // 4.
    do {
        sv.push_back(p);                        // 5.
    } while ((p = std::strtok(NULL, delim)));   // 6.
    delete[] buffer;
    return;
}

Data::Data(std::string file)
{
    extent = new double[6] ;
    extent[0] = std::numeric_limits<double>::max() ;
    extent[1] = std::numeric_limits<double>::min() ;
    extent[2] = std::numeric_limits<double>::max() ;
    extent[3] = std::numeric_limits<double>::min() ;
    extent[4] = std::numeric_limits<double>::max() ;
    extent[5] = std::numeric_limits<double>::min() ;

    if(file.size()==0 )
    {
        file = "/Users/lidan/CLionProjects/marchingcube/useData/head1.vtk" ;
    }
//    int length = std::to_string(size).size() ;
//
//    for(int i = 1;i<100;i++)
//    {
//        std::string file = std::to_string(i) ;
//        while(length-file.length()>0) file="0"+file ;
//        file+=".jpg" ;
//        strs->InsertNextValue(path+file) ;
//        std::cout<<file<<endl ;
//    }

    std::string buffer ;
    std::ifstream infile(file);
    for(int i  =0;i<5;i++)
    {
        std::getline(infile,buffer) ;
        std::cout<<buffer<<std::endl ;
    }
//    std::vector<std::string> temp ;
//    split(file,temp," ");
//    std::vector<std::string>::const_iterator iter = temp.begin();
//    std::cout<<*iter<<":"<<std::endl ;
//    ++iter ;
//    image_x = atoi((*iter).c_str()) ;
//    ++iter ;
//    image_y = atoi((*iter).c_str()) ;
//    ++iter ;
//    image_z = atoi((*iter).c_str()) ;

    std::string temp ;
    std::istringstream str(buffer);
    str>>temp ;
    std::cout<<temp<<std::endl ;
    str>>image_x ;
    str>>image_y ;
    str>>image_z ;
    str.clear() ;


    std::getline(infile,buffer) ;
    str.str(buffer) ;
    str>>temp ;
    std::cout<<temp<<std::endl ;
    str>>space_x ;
    str>>space_y ;
    str>>space_z ;
    str.clear() ;


    std::getline(infile,buffer) ;
    str.str(buffer) ;
    str>>temp ;
    std::cout<<temp<<std::endl ;
    str>>origin_x ;
    str>>origin_y ;
    str>>origin_z ;
    str.clear() ;



    std::getline(infile,buffer) ;
    str.str(buffer) ;
    str>>temp ;
    std::cout<<temp<<std::endl ;
    str>>numbers ;
    str.clear() ;
    std::getline(infile,buffer) ;
    std::getline(infile,buffer) ;

    int count = 0;
    values = (int*)malloc(sizeof(int)*numbers);
    int tint  = 0;

    while(std::getline(infile,buffer))
    {
        str.clear() ;
        str.str(buffer) ;
        while (!str.eof())
        {
            str>>tint ;
//            std::cout<<std::to_string(tint)<<" ";
            values[count++] = tint;
            if(count>=numbers) break;
            if(count%9==0)
            {
//                std::cout<<std::endl ;
                break;
            }
        }
//        std::cout<<"yiline end"<<std::endl ;
    }

    lastpointsEdgeIds = (int*)malloc(sizeof(int)*numbers*3) ;
    for(int i  =0 ;i<numbers*3;i++)
    {
        lastpointsEdgeIds[i] = -1;
    }

    infile.close() ;


}

int Data::getVertexVal(int x, int y, int z)
{
    if(x>image_x||x<0||y>image_y||y<0||z>image_z||z<0)
    {
        return INT_MIN ;
    }
    return values[x+y*image_x+z*image_x*image_y] ;
}


double* Data::getVertexLoc(int x,int y,int z)
{
    if(x>image_x||x<0||y>image_y||y<0||z>image_z||z<0)
    {
        return nullptr ;
    }
    double* result = new double[3] ;
    result[0] = origin_x+x*space_x;
    result[1] = origin_y+y*space_y ;
    result[2] = origin_z+z*space_z ;
    return result ;
}
int Data::getIdx(int x,int y,int z)
{
    return x+y*image_x+z*image_x*image_y ;
}
Point* Data::getVertexXedgeP(int x,int y,int z,int thre)
{
    int idx = getIdx(x,y,z) ;
    if(lastpointsEdgeIds[idx*3]!=-1)
    {
        return lastPoints[lastpointsEdgeIds[idx*3]] ;
    }
    double* Location = getVertexLoc(x,y,z) ;

    int value = getVertexVal(x,y,z) ;
    int xvalue = getVertexVal(x+1,y,z) ;
    double bili = ((double)(thre-value))/(xvalue-value) ;
    if(bili>1||bili<0)
    {
        return nullptr ;
    }

    Location[0]  += space_x*bili ;

    Point* result = new Point(Location,lastPoints.size()) ;
    lastPoints.push_back(result) ;
    lastpointsEdgeIds[idx*3] = lastPoints.size()-1;

    return result ;
}


Point* Data::getVertexYedgeP(int x,int y,int z,int thre)
{
    int idx = getIdx(x,y,z) ;

    if(lastpointsEdgeIds[idx*3+1]!=-1)
    {
        return lastPoints[lastpointsEdgeIds[idx*3+1]] ;
    }
    double* Location = getVertexLoc(x,y,z) ;

    int value = getVertexVal(x,y,z) ;
    int yvalue = getVertexVal(x,y+1,z) ;


    double bili = ((double)(thre-value))/(yvalue-value) ;
    if(bili>1||bili<0)
    {
        return nullptr ;
    }

    Location[1]  += space_y*bili ;

    Point* result = new Point(Location,lastPoints.size()) ;
    lastPoints.push_back(result) ;
    lastpointsEdgeIds[idx*3+1] = lastPoints.size()-1;

    return result ;
}


Point* Data::getVertexZedgeP(int x,int y,int z,int thre)
{

    int idx = getIdx(x,y,z) ;

    if(lastpointsEdgeIds[idx*3+2]!=-1)
    {
        return lastPoints[lastpointsEdgeIds[idx*3+2]] ;
    }
    double* Location = getVertexLoc(x,y,z) ;

    int value = getVertexVal(x,y,z) ;
    int zvalue = getVertexVal(x,y,z+1) ;


    double bili = ((double)(thre-value))/(zvalue-value) ;
    if(bili>1||bili<0)
    {
        return nullptr ;
    }

    Location[2]  += space_y*bili ;

    Point* result = new Point(Location,lastPoints.size()) ;
    SetExtent(result) ;
    lastPoints.push_back(result) ;
    lastpointsEdgeIds[idx*3+2] = lastPoints.size()-1;

    return result ;

}

void Data::SetExtent(Point* point)
{
    if(point->x()<extent[0]) {
        extent[0] = point->x();
    }
    if(point->x()>extent[1])
    {
        extent[1] = point->x() ;
    }

    if(point->y()<extent[2]) {
        extent[2] = point->y();
    }
    if(point->y()>extent[3])
    {
        extent[3] = point->y() ;
    }

    if(point->z()<extent[4]) {
        extent[4] = point->z();
    }
    if(point->z()>extent[5])
    {
        extent[5] = point->z() ;
    }

}

void Data::normalPoints()
{
    for(int i  =0 ;i<lastPoints.size();i++)
    {
        lastPoints[i]->setX((lastPoints[i]->x()-extent[0])/(extent[1]-extent[0])) ;
        lastPoints[i]->setY((lastPoints[i]->y()-extent[2])/(extent[3]-extent[2])) ;
        lastPoints[i]->setZ((lastPoints[i]->z()-extent[4])/(extent[5]-extent[4])) ;
    }
}