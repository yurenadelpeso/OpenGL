#include "luz.h"

Luz::Luz(GLenum mod, Tupla4f posicio, Tupla4f ambient, Tupla4f difus, Tupla4f especula){
    modo = mod;
    posicion = posicio;
    ambiente = ambient;
    difusa = difus;
    especular = especula;
}

void Luz::conmutar(bool activa){

    if(activa){
        glEnable(modo);
        glLightfv(modo, GL_POSITION, posicion);
        glLightfv(modo, GL_AMBIENT, ambiente);
        glLightfv(modo, GL_DIFFUSE, difusa);
        glLightfv(modo, GL_SPECULAR, especular);
        rotacion();
    }else{
        glDisable(modo);
    }
}

void Luz::rotar(int angul,  int x,  int y,  int z){
    assert(x == 1 || x == 0);
    assert(y == 1 || y == 0);
    assert(z == 1 || z == 0);

    rotacionX = x;
    rotacionY = y;
    rotacionZ = z;

    angulo = (angulo + angul) % 360;
    glPushMatrix();
        glRotatef(angulo, x, y, z);
        glLightfv(modo, GL_POSITION, posicion);
    glPopMatrix();
}

void Luz::rotacion(){
    glPushMatrix();
        glRotatef(angulo, rotacionX, rotacionY, rotacionZ);
        glLightfv(modo, GL_POSITION, posicion);
    glPopMatrix();
}