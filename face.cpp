#include "face.h"

point camera(0,0,3);
point eye(1,1,3);
point center(0,0,0);

point m2v(matrix m) {
    return point(m[0][0]/m[3][0], m[1][0]/m[3][0], m[2][0]/m[3][0]);
}

matrix v2m(point v) {
    matrix m(4, 1);
    m[0][0] = v.getCoorX();
    m[1][0] = v.getCoorY();
    m[2][0] = v.getCoorZ();
    m[3][0] = 1.f;
    return m;
}

matrix viewport(int x, int y, int w, int h) {
    matrix m = matrix::identity(4);
    m[0][3] = x+w/2.f;
    m[1][3] = y+h/2.f;
    m[2][3] = 255/2.f;

    m[0][0] = w/2.f;
    m[1][1] = h/2.f;
    m[2][2] = 255/2.f;
    return m;
}
point prod_croix(point up,point z){
    point p;
    p.setCoorX(up.getCoorY() * z.getCoorZ() - up.getCoorZ() * z.getCoorY());
    p.setCoorY(up.getCoorZ() * z.getCoorX() - up.getCoorX() * z.getCoorZ());
    p.setCoorZ(up.getCoorX() * z.getCoorY() - up.getCoorY() * z.getCoorX());
    return p;
}
matrix lookat(point eye, point center, point up) {
    point temp = {eye.getCoorX() - center.getCoorX(),eye.getCoorY() - center.getCoorY(),eye.getCoorZ() - center.getCoorZ()};
    point z = temp.normalize();


    point temp2 = prod_croix(up,z);
    point x = temp2.normalize();

    point temp3 = prod_croix(z,x);
    point y = temp3.normalize();

    
    
    matrix res = matrix::identity(4);
    for (int i=0; i<3; i++) {
        if (i == 0)
        {
            res[0][i] = x.getCoorX();
            res[1][i] = y.getCoorX();
            res[2][i] = z.getCoorX();
            res[i][3] = -center.getCoorX();
        }else if (i == 1)
        {
            res[0][i] = x.getCoorY();
            res[1][i] = y.getCoorY();
            res[2][i] = z.getCoorY();
            res[i][3] = -center.getCoorY();
        }else{
            res[0][i] = x.getCoorZ();
            res[1][i] = y.getCoorZ();
            res[2][i] = z.getCoorZ();
            res[i][3] = -center.getCoorZ();
        }    
    }
    return res;
}

face::face(point un, point deux, point trois , int height , int width,point vt1, point vt2, point vt3)
{
    matrix ModelView = lookat(eye,center,point(0,1,0));

    matrix Projection = matrix::identity(4);
    
    matrix ViewPort   = viewport(width/8, height/8, width*3/4, height*3/4);
    
    point temp = {eye.getCoorX() - center.getCoorX(),eye.getCoorY() - center.getCoorY(),eye.getCoorZ() - center.getCoorZ()};
    Projection[3][2] = -1.f/temp.norm();


    fa.push_back(un);
    fa.push_back(deux);
    fa.push_back(trois);

    point p1(un.getCoorX()*(width/2) + width/2 ,un.getCoorY()*(height/2) + height/2,0);
    point p2(deux.getCoorX()*(width/2) + width/2 ,deux.getCoorY()*(height/2) + height/2,0);
    point p3(trois.getCoorX()*(width/2) + width/2 ,trois.getCoorY()*(height/2) + height/2,0);
    
    faPixel.push_back(p1);
    faPixel.push_back(p2);
    faPixel.push_back(p3);

    vertexTexture.push_back(vt1);
    vertexTexture.push_back(vt2);
    vertexTexture.push_back(vt3);
    
    pointsProjection.push_back(m2v(ViewPort*Projection*ModelView*matrix(un)));
    pointsProjection.push_back(m2v(ViewPort*Projection*ModelView*matrix(deux)));
    pointsProjection.push_back(m2v(ViewPort*Projection*ModelView*matrix(trois)));
}

face::face()
{

    
}

face::~face(){

}

point face::getPointF(int num){ 
    return fa[num];
    }

point face::getPointFP(int num){ 
    return faPixel[num];
    }

int face::sizeF(){
    return fa.size();
}

int face::sizeFP(){
    return faPixel.size();
}

std::vector<point> face::getFaPixel(){
    return faPixel;
}

std::tuple<bool,TGAColor> face::shadingRender(){
    // la lumière
    point light(0,0,-1);

    // Les trois points du triangle
    point vA = fa.at(0);
    point vB = fa.at(1);
    point vC = fa.at(2);
    
    // Vecteur AB
    double x = vB.getCoorX() - vA.getCoorX();
    double y = vB.getCoorY() - vA.getCoorY();
    double z = vB.getCoorZ() - vA.getCoorZ();

    // Vecteur AC
    double x2 = vC.getCoorX() - vA.getCoorX();
    double y2 = vC.getCoorY() - vA.getCoorY();
    double z2 = vC.getCoorZ() - vA.getCoorZ();

    // normale des deux vecteurs
    point p1(y*z2 - z*y2,  z*x2 - x*z2  ,  x*y2 - y*x2);

    // Passer la normale en vecteur unitaire
    double longueur = sqrt((p1.getCoorX()*p1.getCoorX())+(p1.getCoorY()*p1.getCoorY())+(p1.getCoorZ()*p1.getCoorZ()));
    point p2(p1.getCoorX() / longueur,p1.getCoorY() / longueur,p1.getCoorZ() / longueur);

    // Calculer le produit scalaire de la direction de la lumière et la normale unitaire pour avoir l'intensité lumineuse
    double intensity = -((light.getCoorX()*p2.getCoorX())+ (light.getCoorY()*p2.getCoorY()) + (light.getCoorZ()*p2.getCoorZ()));
    return {intensity<0, TGAColor(255*intensity,255*intensity,255*intensity,255)};
    
}

double face::getIntensity(){
    // la lumière
    point light(0,0,-1);
    //point light = point(1,-1,1).normalize();

    // Les trois points du triangle
    point vA = fa.at(0);
    point vB = fa.at(1);
    point vC = fa.at(2);
    
    // Vecteur AB
    double x = vB.getCoorX() - vA.getCoorX();
    double y = vB.getCoorY() - vA.getCoorY();
    double z = vB.getCoorZ() - vA.getCoorZ();

    // Vecteur AC
    double x2 = vC.getCoorX() - vA.getCoorX();
    double y2 = vC.getCoorY() - vA.getCoorY();
    double z2 = vC.getCoorZ() - vA.getCoorZ();


    // normale des deux vecteurs
    point p1(y*z2 - z*y2,  z*x2 - x*z2  ,  x*y2 - y*x2);

    // Passer la normale en vecteur unitaire
    double longueur = sqrt((p1.getCoorX()*p1.getCoorX())+(p1.getCoorY()*p1.getCoorY())+(p1.getCoorZ()*p1.getCoorZ()));
    point p2(p1.getCoorX() / longueur,p1.getCoorY() / longueur,p1.getCoorZ() / longueur);

    // Calculer le produit scalaire de la direction de la lumière et la normale unitaire pour avoir l'intensité lumineuse
    double intensity = -((light.getCoorX()*p2.getCoorX())+ (light.getCoorY()*p2.getCoorY()) + (light.getCoorZ()*p2.getCoorZ()));
    return intensity;
    
}

point face::getPointVT(int num){ 
    return vertexTexture[num];
    }




point face::getPointProjection(int num){
        return pointsProjection.at(num);
}