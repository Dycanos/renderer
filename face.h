#ifndef __FACE_H__
#define __FACE_H__

#include "point.h"
#include "tgaimage.h"
#include <vector>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <tuple>
#include <cmath>
#include <limits>

#include "math.h"
#include "matrix.h"
class face
{
private:
        std::vector<point> fa;
        std::vector<point> faPixel;
        std::vector<point> vertexTexture;
        std::vector<point> pointsProjection;
        

public:
    face();
    face(point un,point deux,point trois,int height,int width,point vt1,point vt2,point vt3);
    ~face();
    point getPointF(int num);
    point getPointFP(int num);
    std::vector<point> getFaPixel();
    void setFaPixel(point p1,point p2,point p3);
    int sizeF();
    int sizeFP();
    std::tuple<bool,TGAColor> shadingRender();
    double getIntensity();
    point getPointVT(int num);
    point getPointProjection(int num);

};

#endif //__FACE_H__