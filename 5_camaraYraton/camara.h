#ifndef CAMARA_H_INCLUDED
#define CAMARA_H_INCLUDED

#include "tuplasg.h"
#include "aux.h"

class Camara{
    Tupla3f eye;
    Tupla3f at;
    Tupla3f up;

    int tipo;
    float left, right, near, far, dzoom;

    public:
        Camara(int tipo, float near, float far, float distancia);

        void girar(int x, int y);
        void zoom(float factor);

        void setObservador() {gluLookAt(eye[0],eye[1],eye[2],at[0],at[1],at[2],up[0],up[1],up[2]); };
        void setProyeccion(float wx, float wy);
};

#endif