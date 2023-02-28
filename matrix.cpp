#include "matrix.h"

matrix::matrix(point v) : mat(std::vector<std::vector<float> >(4, std::vector<float>(1, 1.f))), lig(4), col(1) {
    mat[0][0] = v.getCoorX();
    mat[1][0] = v.getCoorY();
    mat[2][0] = v.getCoorZ();
}
matrix::matrix(int ligne, int colonne) : mat(std::vector<std::vector<float> >(ligne, std::vector<float>(colonne, 0.f))), lig(ligne), col(colonne) {}
matrix::~matrix(){

}
int matrix::nblignes() {
    return lig;
}

int matrix::nbcolonnes() {
    return col;
}


matrix::matrix(){}

matrix matrix::identity(int dimension) {
    matrix M(dimension, dimension);
    for (int i=0; i<dimension; i++) {
        for (int j=0; j<dimension; j++) {
            M[i][j] = (i==j ? 1.f : 0.f);
        }
    }
    return M;
}

std::vector<float>& matrix::operator[](const int i) {
    assert(i>=0 && i<lig);
    return mat[i];
}

matrix matrix::operator*(const matrix& a) {
    assert(col == a.lig);
    matrix operat(lig, a.col);
    for (int i=0; i<lig; i++) {
        for (int j=0; j<a.col; j++) {
            operat.mat[i][j] = 0.f;
            for (int k=0; k<col; k++) {
                operat.mat[i][j] += mat[i][k]*a.mat[k][j];
            }
        }
    }
    return operat;
}

matrix matrix::transposition(){
    matrix maTranspo(col, lig);
    for(int i=0; i<lig; i++)
        for(int j=0; j<col; j++)
            maTranspo[j][i] = mat[i][j];
    return maTranspo;
}

matrix matrix::inverser() {
    assert(lig==col);
    matrix matInverser(lig, col*2);
    for(int i=0; i<lig; i++)
        for(int j=0; j<col; j++)
            matInverser[i][j] = mat[i][j];
    for(int i=0; i<lig; i++)
        matInverser[i][i+col] = 1;
    // premier passage
    for (int i=0; i<lig-1; i++) {
        // normaliser la première ligne
        for(int j=matInverser.col-1; j>=0; j--)
            matInverser[i][j] /= matInverser[i][i];
        for (int k=i+1; k<lig; k++) {
            float coeff = matInverser[k][i];
            for (int j=0; j<matInverser.col; j++) {
                matInverser[k][j] -= matInverser[i][j]*coeff;
            }
        }
    }
    // normaliser la dernière ligne
    for(int j=matInverser.col-1; j>=lig-1; j--)
        matInverser[lig-1][j] /= matInverser[lig-1][lig-1];
 
    // deuxième passage
    for (int i=lig-1; i>0; i--) {
        for (int k=i-1; k>=0; k--) {
            float coeff = matInverser[k][i];
            for (int j=0; j<matInverser.col; j++) {
                matInverser[k][j] -= matInverser[i][j]*coeff;
            }
        }
    }

    // réduction de la matrice d'identité
    matrix tronquage(lig, col);
    for(int i=0; i<lig; i++)
        for(int j=0; j<col; j++)
            tronquage[i][j] = matInverser[i][j+col];
    return tronquage;
}
