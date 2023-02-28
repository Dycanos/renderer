#include "affichage.h"
#include <iostream>


affichage::affichage(std::string str)
{

}

affichage::~affichage(){

}

void affichage::line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) { 
    bool steep = false; 
    if (std::abs(x0-x1)<std::abs(y0-y1)) { // if the line is steep, we transpose the image 
        std::swap(x0, y0); 
        std::swap(x1, y1); 
        steep = true; 
    } 
    if (x0>x1) { // make it left−to−right 
        std::swap(x0, x1); 
        std::swap(y0, y1); 
    } 
    for (int x=x0; x<=x1; x++) { 
        float t = (x-x0)/(float)(x1-x0); 
        int y = y0 + (y1 - y0)*t; 
        if (steep) { 
            image.set(y, x, color); // if transposed, de−transpose 
        } else { 
            image.set(x, y, color); 
        } 
    } 
}   

double affichage::area(double x1, double y1, double x2, double y2, double x3, double y3)
{
    return (x1*(y2-y3) + x2*(y3-y1)+ x3*(y1-y2))/2.0;
}


bool affichage::isInside(double x1, double y1, double x2, double y2, double x3, double y3, double x, double y,point &bary)
{
    double A = area (x1, y1, x2, y2, x3, y3);
    double A1 = area (x, y, x2, y2, x3, y3);
    double A2 =  area (x1, y1, x, y, x3, y3);
    double A3 = area (x1, y1, x2, y2, x, y);

    double alpha = (double)A2 / (double)A;
    double beta = (double)A3 / (double)A;
    double gamma = (double)A1 / (double)A;
    
    bary.setCoorX(alpha);
    bary.setCoorY(beta);
    bary.setCoorZ(gamma);


    return alpha > -0.01 && beta > -0.01 && gamma > -0.01; 
}


