#include "camara.h"

Camara::Camara(int tip0, float near, float far, float zoom){
    this->tipo = tipo;
    this->near = near;
    this->far = far;
    eye = {0,0,zoom};
    at = {0,0,0};
    up = {0,1,0};
    dzoom = zoom;
}

void Camara::girar(int x, int y){
    x = x%360;
    y = y%360;

    eye[0]= dzoom*sin((-y*M_PI)/180) * cos((-x*M_PI)/180);
    eye[1]= dzoom*sin((x*M_PI)/180);
    eye[2]= dzoom*cos((y*M_PI)/180) * cos((x*M_PI)/180);
    
    if ((x > 90 && x <270) || (x < -90 && x > -270)){
        up[1] = -1;
    }else{
        up[1] = 1;
    }
}

void Camara::zoom(float radio){

    if(dzoom < 10 && radio > 0 ){
        radio = 0;
    }
    dzoom -= radio;
    
    setProyeccion(left,right);
}

void Camara::setProyeccion(float wx, float wy){

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    left = wx;
    right = wy;
    
    if(tipo == 0){
        glFrustum(-wx*dzoom, +wx*dzoom, -wy*dzoom, +wy*dzoom, near, far);
    }else{
        glOrtho(-wx*dzoom, +wx*dzoom, -wy*dzoom, +wy*dzoom, near, far);
    }
    
}