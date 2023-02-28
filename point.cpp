#include "point.h"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

point::point(float x, float y, float z){
    coorX = x;
    coorY = y;
    coorZ = z;
}

point::point(){

}

point::~point(){

}

float point::getCoorX(){return coorX;}
float point::getCoorY(){return coorY;}
float point::getCoorZ(){return coorZ;}

void point::setCoorX(float i){ coorX = i;}
void point::setCoorY(float i){ coorY = i;}
void point::setCoorZ(float i){ coorZ = i;}

point point::normalize(){
    point resultat;
    resultat.setCoorX(this->getCoorX()*(1/norm()));
    resultat.setCoorY(this->getCoorY()*(1/norm()));
    resultat.setCoorZ(this->getCoorZ()*(1/norm()));

    return resultat;
}