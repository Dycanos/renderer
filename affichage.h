#ifndef __AFFICHAGE_H__
#define __AFFICHAGE_H__

#include <vector>
#include "tgaimage.h"
#include "point.h"

class affichage
{
public:
    affichage(std::string str);
    ~affichage();
    void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color);
    double area(double x1, double y1, double x2, double y2, double x3, double y3);
    bool isInside(double x1, double y1, double x2, double y2, double x3, double y3, double x, double y,point &bary);
};

#endif //__AFFICHAGE_H__
