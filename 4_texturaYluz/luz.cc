#include "luz.h"

Luz::Luz(GLenum id, Tupla4f posicio, Tupla4f ambient, Tupla4f difus, Tupla4f especula){
    idLuz = id;
    posicion = posicio;
    ambiente = ambient;
    difusa = difus;
    especular = especula;
}

void Luz::conmutar(bool activa){
    std::cout<< "Entrando en conmutar:: valor del id  "<<idLuz<<"Estado actual "<< activa<< "\n";

    if(activa){
        glEnable(idLuz);
        glLightfv(idLuz, GL_POSITION, posicion);
        glLightfv(idLuz, GL_AMBIENT, ambiente);
        glLightfv(idLuz, GL_DIFFUSE, difusa);
        glLightfv(idLuz, GL_SPECULAR, especular);
        rotacion();
    }else{
        glDisable(idLuz);
    }
    std::cout<<"EStado de salida  "<< activa<<"\n";
}



void Luz::rotar(int angulo, unsigned int x, unsigned int y, unsigned int z){
 //std::cout<< "ROTAR ANGULO "<<angulo<<"X Y Z "<< x<<y<<z <<"\n";

    
    assert(x == 1 || x == 0);
    assert(y == 1 || y == 0);
    assert(z == 1 || z == 0);

    this->rotacionX = x;
    this->rotacionY = y;
    this->rotacionZ = z;

    this->angulo = (this->angulo + angulo) % 360;
    glPushMatrix();
        glRotatef(this->angulo, x, y, z);
        glLightfv(idLuz, GL_POSITION, posicion);
    glPopMatrix();
}




void Luz::rotacion(){
    glPushMatrix();
        glRotatef(this->angulo, rotacionX, rotacionY, rotacionZ);
        glLightfv(idLuz, GL_POSITION, posicion);
    glPopMatrix();
}
