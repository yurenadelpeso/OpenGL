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
// ESTRUCTURA DE LOS MATERIALES
//
// *****************************************************************************
struct Material {
    Tupla4f ambiente;
    Tupla4f difusa;
    Tupla4f especular;
    GLfloat brillo[1];
};

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class ObjMallaIndexada
{
   
   public:
 
  bool usarDiferido=0;
   std::vector<Tupla3i> triangulos ;
   void draw_ModoInmediato();// dibuja el objeto en modo inmediato
   void draw_ModoDiferido();// dibuja el objeto en modo diferido (usando VBOs)
   void draw(int modoDibujo, bool usarDiferido);  // función que redibuja el objeto.está función llama a 'draw_MI' (modo inmediato)o bien a 'draw_MD' (modo diferido, VBOs)
   void prepara_textura(); //para imagenes jpg prepara la textura jpg (práctica 4)
   void aplicar_materiales(); // calcula tabla de normales de vértices (práctica 3)
   void seleccionar();
   void ajedrezado();
   void draw_seleccion(int modo_vis);
   protected:
   //void aplicar_materiales();
   void calcular_normales_vertices();
   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)
   std::vector<Tupla3f> vertices ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
                                    // una terna de 3 enteros por cada cara o triángulo
   //std::vector<Tupla4d> colores; // completar: tabla de colores, tabla de normales de vértices
   
   std::vector<Tupla3i> colorVerticesPares;
   std::vector<Tupla3i> colorVerticesImpares;
   //necesarios para el modo diferido
   GLuint id_VboVertices=0;
   GLuint id_VboTriangulos=0;
   GLuint id_VboColor=0;
   float radio_base=1;
   float altura=1;

   //MATERIALES
   Material material;
   Material Esmeralda{
     { 0.022, 0.175, 0.022, 1.0 },
     { 0.076, 0.614, 0.076, 1.0 },
     { 0.633, 0.728, 0.633, 1.0 },
     { 76.8 },
    };
  Material Bronce{
    { 0.213, 0.128, 0.054, 1.0 },
    { 0.714, 0.428, 0.181, 1.0 },
    { 0.394, 0.272, 0.167, 1.0 },
    { 25.6 },
    };
  Material Blanco{
    {0.05,0.05,0.05,1.0},
    {0.5,0.5,0.5,1.0},
    {0.7,0.7,0.7,1.0},
    { 0.078125},
  };

   //TEXTURAS
   GLuint id_textura=0;
    std::vector<Tupla2f>verticesTextura; // una tupla de 2 float por cada vertice
    std::string nombre_archivo;

   //NORMALES
   std::vector<Tupla3f> verticesNormales;
   std::vector<Tupla3f> triangulosNormales; 
   //bool verticesNormalizados=false;
  // bool triangulosNormalizados=false;

   //CAMARA
    bool seleccionado = false;
    std::vector<Tupla3f> color;
    std::vector<Tupla3f> colorAnterior;

    Material materialAnterior;
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


//TETRAEDRO: CENTRO EN EL ORIGEN Y LADO UNIDAD
//TIENE CUATRO VERTICES Y CUATRO CARAS
class Tetraedro : public ObjMallaIndexada
{
   public:
   Tetraedro() ;

} ;

// *****************************************************************************
// objeto leído de un archivo PLY

class ObjPLY : public ObjMallaIndexada
{
   public:
      ObjPLY( const std::string & nombre_archivo );

} ;

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

class ObjRevolucion : public ObjMallaIndexada

{

   public:

      ObjRevolucion();//constructor por defecto necesario para las clases herederas
      ObjRevolucion( const std::string & nombre_ply_perfil, int nrev );
      ObjRevolucion( const std::string & nombre_ply_perfil );
      
      void crear_malla( const std::vector<Tupla3f> & perfil,const int instanciasPerfil ) ;
      //void crear_malla_2( const std::vector<Tupla3f> & perfil,int instanciasPerfil ) ;
      void tapas(float a, int b);

      /*********************************************************************************************
      //SI TUVIERA QUE COMPROBAR QUE LAS COORDENADAS ESTÁN ORDENADAS DE MENOR Y A MAYOR Y 
      //POSICION PRIMERA D3EL VECTOR PERFIL, PERFIL[1][i]
      //void tablaverticesordenada(const std::vector<Tupla3f> & perfil);
      ***************************************************************************************************/
} ;


class Cuadro : public ObjMallaIndexada{
   public:
       Cuadro(const std::string &nombre_archivo, const std::vector<Tupla2f> textura_vertices);
};


class Cilindro : public ObjRevolucion{  
   public:
      Cilindro(const int num_vert_perfil, const int num_instancias_perf);
};

class Cono : public ObjRevolucion{ 
   public:
      Cono();
      Cono(const int num_vert_perfil, const int num_instancias_perf);
};

class Esfera : public ObjRevolucion{  
   public:
      Esfera(const int num_vert_perfil, const int num_instancias_perf);      
};


#endif
