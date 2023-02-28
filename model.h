#ifndef __MODEL_H__
#define __MODEL_H__

#include <vector>
#include "point.h"
#include "face.h"
#include "tgaimage.h"
#include "affichage.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <random>

class model
{
private:
        std::vector<point> v;
        std::vector<face> f;
        std::vector<point> vt;

public:
    model(const char *filename,int height,int width);
    ~model();
    point vert(int idx);
    std::vector<point> getV();
    std::vector<face> getF();
    std::vector<point> getVT();
    int sizeF();
    void lancement(TGAImage &image, TGAColor color,affichage affi,float *zbuffer,TGAImage texture,TGAImage normal);
    void dessineTriangle(point p1,point p2,point p3,TGAImage &image, TGAColor color,affichage affi,float *zbuffer,TGAImage texture,point vt1,point vt2,point vt3,double intensity,TGAImage normal);
    TGAColor randomize_color();
    bool fragment(TGAColor &normal, TGAColor &color, point &bary);
};

#endif //__MODEL_H__