// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: ObjMallaIndexada.h
// -- declaraciones de clase ObjMallaIndexada (mallas indexadas) y derivados
//
// #############################################################################

#ifndef OBJETOS_H_INCLUDED
#define OBJETOS_H_INCLUDED

#include "aux.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class ObjMallaIndexada
{
   
   public:
   void ajedrezado();
   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato();
   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido();
   // función que redibuja el objeto
   // está función llama a 'draw_MI' (modo inmediato)
   // o bien a 'draw_MD' (modo diferido, VBOs)
   void draw(int modo, bool ajedrez) ;
 

   protected:
   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)
   std::vector<Tupla3f> vertices ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> triangulos ; // una terna de 3 enteros por cada cara o triángulo
   // completar: tabla de colores, tabla de normales de vértices
   //std::vector<Tupla3f> color ; 
   
   //necesarios para el modo diferido
   GLuint id_VboVertices=0;
   GLuint id_VboTriangulos=0;
   GLuint id_VboColor=0;
   float radio_base=1;
   float altura=1;
   int modo=0;

   //NORMALES
 
   
   std::vector<Tupla3i> colorVerticesPares;
   std::vector<Tupla3i> colorVerticesImpares;
   std::vector<Tupla3f> colorTriangulo;
   std::vector<Tupla3f> colores;
   std::vector<Tupla3f> color;





} ;

// *****************************************************************************
//
// clases derivadas de ObjMallaIndexada (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cubo con centro en el origen y lado unidad
// (tiene 9 vertices y 6 caras)

class Cubo : public ObjMallaIndexada
{
   public:
   Cubo() ;

} ;
class Frontera : public ObjMallaIndexada
{
   public:
   Frontera(float tam) ;

} ;

//TETRAEDRO: CENTRO EN EL ORIGEN Y LADO UNIDAD
//TIENE CUATRO VERTICES Y CUATRO CARAS
class Tetraedro : public ObjMallaIndexada
{
   public:
   Tetraedro() ;

} ;










// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)



class ObjRevolucion : public ObjMallaIndexada

{
private:
   float tam;

   public:

      ObjRevolucion();//constructor por defecto necesario para las clases herederas
      ObjRevolucion( const std::string & nombre_ply_perfil, int nrev );
      void crearMalla( const std::vector<Tupla3f> & perfil,
                       const int instanciasPerfil ) ;
      void crearMallaSinTapas( const std::vector<Tupla3f> & perfil,
                        int instanciasPerfil ) ;
     
      void ponerTapas(float a, int b);
      float tamFrontera();

      /*********************************************************************************************
      //SI TUVIERA QUE COMPROBAR QUE LAS COORDENADAS ESTÁN ORDENADAS DE MENOR Y A MAYOR Y 
      //POSICION PRIMERA D3EL VECTOR PERFIL, PERFIL[1][i]
      //void tablaverticesordenada(const std::vector<Tupla3f> & perfil);
      ***************************************************************************************************/

      //std::vector<Tupla3f> detectarTapa(const std::vector<Tupla3f> & perfil_original);

      ObjRevolucion( const std::string & nombre_ply_perfil );
/*
      //funcion auxiliar para ordenar una tablña de vertices??
      void tablaverticesordenada(const std::vector<Tupla3f> & perfil_original);*/

      void calcularVerticesNormales();
      void calcularTriangulosNormales();
   
      


} ;




class Cilindro : public ObjRevolucion
{
   private:
      float tam;
   public:
      Cilindro(const int num_vert_perfil, const int num_instancias_perf);
      float tamFrontera(){return tam;}


};

class Cono : public ObjRevolucion
{
   
   public:
      Cono();
      Cono(const int num_vert_perfil, const int num_instancias_perf);
      

};
class Esfera : public ObjRevolucion
{
   
   public:
      Esfera(const int num_vert_perfil, const int num_instancias_perf);
      

};
#endif
