#ifndef __MATRIX_H__
#define __MATRIX_H__

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
#include <vector>
#include <cassert>
#include <cmath>
#include <iostream>

#include "math.h"

const int ALLOCATION=4;

class matrix
{
private:
        std::vector<std::vector<float> > mat;
        int col;
        int lig;

public:
    matrix();
    matrix(int ligne = ALLOCATION,int colonne= ALLOCATION);
    ~matrix();
    matrix(point v);
    int nblignes();
    int nbcolonnes();
    static matrix identity(int dimensions);
    matrix transposition();
    matrix inverser();
    std::vector<float>& operator[](const int i);
    matrix operator*(const matrix& a);
};

#endif //__Matrix_H__