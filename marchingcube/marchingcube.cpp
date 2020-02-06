//
// Created by 李源 on 2020-02-05.
//

#include "marchingcube.h"




void Marchingcube::run()
{

    for(int i  =0 ;i<_data.size_z()-1;i++)
    {
        for(int j =0 ;j <_data.size_y()-1;j++)
        {
            for(int k  =0 ;k<_data.size_z()-1;k++)
            {
                processOneCube(i,j,k) ;
            }
        }
    }


}
void Marchingcube::processOneCube(int x ,int y,int z)
{
    Point* result[12] ;
    std::vector<int> cellvals ;
    unsigned char cubeindex  = 0 ;
    if(_data.getVertexVal(x,y,z)<_thre) cubeindex |= 1;
    if(_data.getVertexVal(x,y+1,z)<_thre) cubeindex |= 2 ;
    if(_data.getVertexVal(x+1,y+1,z)<_thre) cubeindex |= 4 ;
    if(_data.getVertexVal(x+1,y,z)<_thre) cubeindex |= 8 ;
    if(_data.getVertexVal(x,y,z+1)<_thre) cubeindex |= 16 ;
    if(_data.getVertexVal(x,y+1,z+1)<_thre) cubeindex |= 32 ;
    if(_data.getVertexVal(x+1,y+1,z+1)<_thre) cubeindex |= 64 ;
    if(_data.getVertexVal(x+1,y,z+1)<_thre) cubeindex |= 128 ;

    if (edgeTable[cubeindex] == 0)
        return ;


    int temp = 1 ;
    int count = 0 ;
    while(count<12)
    {
        if(edgeTable[cubeindex]&temp)
        {
            result[count] = getEdge(count,x,y,z) ;
        }
        count++ ;
        temp*=2;
    }

    for (int i=0;triTable[cubeindex][i]!=-1;i+=3) {
        int * idx = new int[3] ;
        idx[0]  = result[triTable[cubeindex][i  ]]->id();
        idx[1] = result[triTable[cubeindex][i+1]]->id();
        idx[2] = result[triTable[cubeindex][i+2]]->id();
        Triangle* newone = new  Triangle(idx) ;
        newone->filter(&_data) ;
        triangles.push_back(newone) ;
    }

}



Point* Marchingcube::getEdge(int idx,int x,int y,int z)
{
    Point* result = nullptr ;

    switch(idx)
    {
        case 0:
            result = _data.getVertexYedgeP(x,y,z,_thre) ;
            break ;
        case 1:
            result = _data.getVertexXedgeP(x,y+1,z,_thre) ;
            break ;
        case 2:
            result = _data.getVertexYedgeP(x+1,y,z,_thre) ;
            break ;
        case 3:
            result = _data.getVertexXedgeP(x,y,z,_thre) ;
            break ;
        case 4:
            result = _data.getVertexYedgeP(x,y,z+1,_thre) ;
            break ;
        case 5:
            result = _data.getVertexXedgeP(x,y+1,z+1,_thre) ;
            break ;
        case 6:
            result = _data.getVertexYedgeP(x+1,y,z+1,_thre) ;
            break ;
        case 7:
            result = _data.getVertexXedgeP(x,y,z+1,_thre) ;
            break ;
        case 8:
            result = _data.getVertexZedgeP(x,y,z,_thre) ;
            break ;
        case 9:
            result = _data.getVertexZedgeP(x,y+1,z,_thre) ;
            break ;
        case 10:
            result = _data.getVertexZedgeP(x+1,y+1,z,_thre) ;
            break ;
        case 11:
            result = _data.getVertexZedgeP(x+1,y,z,_thre) ;
            break ;

    }
    return result ;

}

void Marchingcube::writeFile(std::string file)
{
   std::ofstream fs(file) ;

   int  pointsize = _data.getPointSize() ;
   for(int i  =0 ;i<pointsize;i++)
   {
       Point* temp = _data.getPoint(i) ;
       fs<<"v "
         <<std::to_string(temp->x())<<" "
         <<std::to_string(temp->y())<<" "
         <<std::to_string(temp->z())<<std::endl ;
   }

    std::vector<Triangle*>::const_iterator iter1 = triangles.begin();
   while(iter1!=triangles.end())
   {
       fs<<"f "<<(*iter1)->to_string()<<std::endl ;
       iter1++ ;
   }

   fs.close() ;
}

double* Marchingcube::getVertexNormalOf(int i)
{
    return normals[i] ;
}

void Marchingcube::computeNormals()
{

    _data.normalPoints() ;
    int verts = _data.getPointSize() ;
    for(int i  = 0; i< verts;i++)
    {
        double* temp = (double*)calloc(3,sizeof(double)) ;
        normals.push_back(temp) ;
    }

    char* count = new char[verts] ;
    for(int i  =0 ;i< verts;i++)
    {
        count[i] = 0;
    }

    for(int i  = 0; i< triangles.size();i++)
    {
        for(int j = 0;j<3;j++)
        {
            double* first = triangles[i]->getNormal(j,&_data) ;
            normals[triangles[i]->getIdx(j)][0] += first[0] ;
            normals[triangles[i]->getIdx(j)][1] += first[1] ;
            normals[triangles[i]->getIdx(j)][2] += first[2] ;
            count[triangles[i]->getIdx(j)]++ ;
        }
    }

    for(int i  =0 ;i<verts;i++)
    {
       for(int j =0 ;j<3;j++)
       {
           normals[i][j] /= count[i];
       }
    }
}