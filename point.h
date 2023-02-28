#ifndef __POINT_H__
#define __POINT_H__

#include <vector>
#include "math.h"
class point
{
private:
        float coorX;
        float coorY;
        float coorZ;

public:
    point(float x,float y,float z);
    point();
    ~point();
    float getCoorX();
    float getCoorY();
    float getCoorZ();
    void setCoorX(float i);
    void setCoorY(float i);
    void setCoorZ(float i);
    float norm () const { return std::sqrt(coorX*coorX+coorY*coorY+coorZ*coorZ); }
    point normalize();
};

#endif //__POINT_H__