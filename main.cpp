#include <cmath>
#include <vector>
#include "tgaimage.h"
#include "model.h"
#include <iostream>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const TGAColor green   = TGAColor(0, 255,   0,   255);

int main(int argc, char** argv) {
    int height = 1000;
    int width = 1000;
    TGAImage image(height, width, TGAImage::RGB);
    TGAImage texture;
    texture.read_tga_file("ressources/african_head_diffuse.tga");
    //Diablo3 texture.read_tga_file("ressources/diablo3_pose_diffuse.tga");
    texture.flip_vertically();
    TGAImage normal;
    normal.read_tga_file("ressources/african_head_nm.tga");
    //Diablo3 normal.read_tga_file("ressources/diablo3_pose_nm.tga");
    normal.flip_vertically();
    model mod("african_head.obj",height,width);
    //Diablo3 model mod("diablo3_pose.obj",height,width);
    
    affichage afficha("");
    float *zbuffer = new float[height*width];
    for (int i=height*width; i--; zbuffer[i] = -std::numeric_limits<float>::max());
    mod.lancement(image,green,afficha,zbuffer,texture,normal);
    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image   
    image.write_tga_file("output.tga");
    return 0;
}