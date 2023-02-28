#include "model.h"


model::model(const char *filename,int height,int width) : v(), f() {
        std::ifstream contenu;    
        contenu.open(filename,std::ifstream::in);
        if (contenu.fail())
        {
            return;
        }
        std::string ligne;
        while (!contenu.eof())
        {
            std::getline(contenu,ligne);
            if (ligne.compare(0,2,"v ") == 0)
            { 
                std::istringstream isstream;
                std::string word;
                isstream.str(ligne);
                getline(isstream, word, ' ');
                float x,y,z;
                getline(isstream, word, ' ');
                x = stof(word);
                getline(isstream, word, ' ');
                y = stof(word);
                getline(isstream, word, ' ');
                z = stof(word);
                point p = point(x,y,z);
                    v.push_back(p);  
            }                
            else if (ligne.compare(0,2,"f ") == 0)
            {
                std::string m1,m2,m3;
                int compteur = 0;
                std::istringstream isstream2;
                std::istringstream isstream3;
                std::istringstream isstream4;
                std::istringstream isstream5;
                std::string word2;
                isstream2.str(ligne);
                getline(isstream2, word2, ' ');
                point un,deux,trois,vt1,vt2,vt3;
                for(int i = 0 ; i<3 ; i++){
                    getline(isstream2, word2, ' ');
                    if (i ==0)
                    {      
                        m1 = word2;
                        isstream3.str(m1);
                        while(getline(isstream3, m1, '/')){
                            if (compteur == 0){
                                un = v.at(stoi(m1)-1);
                            }
                                
                            if (compteur == 1)
                                vt1 = vt.at(stoi(m1)-1);  
                            compteur++;   
                        }
                        compteur=0;
                    }
                    else if(i == 1){
                            m2 = word2;
                            isstream4.str(m2);
                            while(getline(isstream4, m2, '/')){
                                if (compteur == 0)
                                    deux = v.at(stoi(m2)-1);
                                if (compteur == 1)
                                    vt2 = vt.at(stoi(m2)-1);
                                compteur++;  
                            }
                            compteur=0;  
                    }else if (i == 2)
                    {
                        m3 = word2;
                        isstream5.str(m3);
                        while(getline(isstream5, m3, '/')){
                            if (compteur == 0)
                                trois = v.at(stoi(m3)-1);
                            if (compteur == 1)
                                vt3 = vt.at(stoi(m3)-1);
                            compteur++;  
                        }
                        compteur=0;
                        
                        face fa = face(un,deux,trois,height,width,vt1,vt2,vt3);
                        
                        f.push_back(fa);
                    }   
                 }   
            }
            else if (ligne.compare(0,3,"vt ") == 0)
            { 
                
                std::istringstream isstream;
                std::string word;
                isstream.str(ligne);
                getline(isstream, word, ' ');
                float x,y,z;
                getline(isstream, word, ' ');
                getline(isstream, word, ' ');
                x = stof(word);
                getline(isstream, word, ' ');
                y = stof(word);
                getline(isstream, word, ' ');
                z = stof(word);
                
                point p = point(x,y,z);
                    vt.push_back(p);  
            }   
        } 
}

model::~model()
{
}

std::vector<face> model::getF(){
    return f;
}

std::vector<point> model::getV(){
    return v;
}

std::vector<point> model::getVT(){
    return vt;
}

point model::vert(int idx) {
    return v[idx];
}

int model::sizeF(){
    return f.size();
}

void model::lancement(TGAImage &image, TGAColor color, affichage affi,float *zbuffer,TGAImage texture,TGAImage normal){
    for (face &fa : f)
    {
        auto [discard, color] = fa.shadingRender();
        
       dessineTriangle(fa.getPointProjection(0),fa.getPointProjection(1),fa.getPointProjection(2),image,color,affi,zbuffer,texture,fa.getPointVT(0),fa.getPointVT(1),fa.getPointVT(2),fa.getIntensity(),normal);      
    }
    }

void model::dessineTriangle(point p1,point p2,point p3,TGAImage &image, TGAColor color,affichage affi,float *zbuffer,TGAImage texture,point vt1,point vt2,point vt3,double intensity,TGAImage normal){
        TGAColor couleur;
        TGAColor couleur_normal;
        int width = image.get_width();
        point bary;

    
        double tempX = image.get_width() - 1;
        double tempY = image.get_height() - 1;

        double boxMinx = std::max(0.,std::min(std::min((double)p1.getCoorX(),(double)p2.getCoorX()),(double)p3.getCoorX()));
        double boxMiny = std::max(0.,std::min(std::min((double)p1.getCoorY(),(double)p2.getCoorY()),(double)p3.getCoorY()));
        double boxMaxx = std::min(tempX,std::max(std::max((double)p1.getCoorX(),(double)p2.getCoorX()),(double)p3.getCoorX()));
        double boxMaxy = std::min(tempY,std::max(std::max((double)p1.getCoorY(),(double)p2.getCoorY()),(double)p3.getCoorY()));

        for (int i = boxMinx;i< boxMaxx;i++) 
        {
            for (int j = boxMiny ;j < boxMaxy;j++) 
            {
                if (affi.isInside(
                    p1.getCoorX(),p1.getCoorY(),
                    p2.getCoorX(),p2.getCoorY(),
                    p3.getCoorX(),p3.getCoorY(),
                    i,j,bary))
                {
                    double x,y;
                    x = bary.getCoorX() * vt2.getCoorX() + bary.getCoorY() * vt3.getCoorX() + bary.getCoorZ() * vt1.getCoorX();
                    y = bary.getCoorX() * vt2.getCoorY() + bary.getCoorY() * vt3.getCoorY() + bary.getCoorZ() * vt1.getCoorY();
                    couleur =texture.get(x*texture.get_width(), y*texture.get_height());
                    couleur_normal =normal.get(x*normal.get_width(), y*normal.get_height());
                    double tmp = 0;
                    tmp = bary.getCoorX() * p1.getCoorZ() + bary.getCoorY() * p2.getCoorZ() + bary.getCoorZ() * p3.getCoorZ();
                    
                    if (zbuffer[i+j*width]<tmp) 
                    {
                        zbuffer[i+j*width] = tmp;
                        
                        bool discard = fragment(couleur_normal,couleur,bary);
                        if (!discard)
                        {
                          image.set(i, j, couleur);
                        }
                        //avec intensity
                        //image.set(i, j, TGAColor(couleur.r * intensity,couleur.g* intensity,couleur.b* intensity,255));
                        //avec lissage
                        //image.set(i, j, couleur);
                    }
                }
                
                
            }
        }
        

}

TGAColor model::randomize_color()
{
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<int> distr(0, 255);
    return TGAColor(distr(engine), distr(engine), distr(engine), 255);
}

bool model::fragment(TGAColor &normal, TGAColor &color, point &bary)
{
    point light_dir(0,0,-1);
    point norm(normal.r * 2. / 255. - 1., normal.g * 2. / 255. - 1., normal.b * 2. / 255. - 1.);
    norm = norm.normalize();
    point light = light_dir.normalize();
    double produitSc = norm.getCoorX() * light.getCoorX() + norm.getCoorY() * light.getCoorY() + norm.getCoorZ() * light.getCoorZ();
    double intensity = std::max(1.25, produitSc);
    point rgb(color.r, color.g, color.b);
    double v = rgb.getCoorX() * norm.getCoorX() + rgb.getCoorY() * norm.getCoorY() + rgb.getCoorZ() * norm.getCoorZ();
    double diffuse = std::min(1., std::max(0., v) / 255.);
    diffuse *= intensity;
    color.r *= diffuse;
    color.g *= diffuse;
    color.b *= diffuse;
    return false;
}
