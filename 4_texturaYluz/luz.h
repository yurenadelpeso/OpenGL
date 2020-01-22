#ifndef LUZ_H_INCLUDED
#define LUZ_H_INCLUDED

#include "tuplasg.h"
#include "aux.h"

class Luz{
    private:
        GLenum idLuz;
        bool activa;
        int angulo = 0;
        
        Tupla4f especular;
        Tupla4f posicion;
        Tupla4f ambiente;
        Tupla4f difusa;
       
        
        int rotacionX = 0;
        int rotacionY = 0;
        int rotacionZ = 0;
        void rotacion();

    public:
        Luz(GLenum idLuz, Tupla4f posicion, Tupla4f ambiente, Tupla4f difusa, Tupla4f especular);
        void conmutar(bool activa);
        void rotar(int angulo, unsigned int x,  unsigned int y, unsigned int z);

};

#endif