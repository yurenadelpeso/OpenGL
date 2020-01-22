#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "jerarquico.h"
#include "luz.h"

//typedef int ModoVis;



class Escena
{
   

   public:
    int  num_instancias_perf=20;
   bool ajedrez= false;

   int modo=0;

   ModoVis modo_vis=0;

  int modeloActual=0;
  bool luz=false;
   

   
   private:
   Ejes ejes;

   // variables que definen la posicion de la camara en coordenadas polares
   GLfloat Observer_distance;
   GLfloat Observer_angle_x;
   GLfloat Observer_angle_y;

   // variables que controlan la ventana y la transformacion de perspectiva
   GLfloat Width, Height, Front_plane, Back_plane;

   // OBJETO_ACTUAL objeto actual (el que se visualiza)
    //NUM_OBJETOS: número de objetos(actualizado al crear los objetos en el constructor)
   int objeto_actual, 
       num_objetos,   
       num_modos  ;

   // Objetos de la escena
   // es importante inicializarlo a 'nullptr'

   //p2
   Cubo * cubo = nullptr ; 
   Tetraedro *tetraedro = nullptr;
   Cilindro *cilindro =nullptr;
   ObjPLY * ply = nullptr;
   ObjRevolucion * plyrev= nullptr;
   Esfera *esfera=nullptr;
   Cono * cono=nullptr;

   //p3
   ObjJerarquico *objJerarquico=nullptr;
   bool animacion=false;
  //para las texturas
  Cuadro* cuadro = nullptr;
  OtroCuadro* C=nullptr;
  OtroCuadro* C1=nullptr;



  // P4
   //para las luces
  bool shadeModel,
       conmutarLuz, 
       conmutarLuzPuntual,
       conmutarLuzPuntual3,
       conmutarLuzPuntual4;

 

 //PARA LAS LUCES

  




  Tupla4f ambiente = {0.0,0.0,0.0,1.0};

 //DIRECCION DE ORIGEN DE LA LUZ
  //( DE DERECHA HACIA EL OBJETO, DE ARRIBA HACIA EL OBEJTO,DE FRENTER AL OBJETO,DESDE ATRAS)
  Tupla4f posicionDireccional = {0.0,0.0,1.0,0.0};
  Tupla4f difusaDireccional = {1.0,1.0,1.0,1.0};
  Tupla4f especularDireccional = {1.0,1.0,1.0,1.0};



  Tupla4f posicionPuntual = {1.0,0.0,1.0,0.0}; // DESDE LA DERECHA
  Tupla4f difusaPuntual = {1.0,0.0,1.0,1.0};
  Tupla4f especularPuntual = {10.0,0.0,10.0,10.0};


  Tupla4f posicionPuntual2 = {0.0,10.0,0.0,0.0};// DESDE ARRIBA
  Tupla4f difusaPuntual2 = {1.0,0.0,1.0,1.0}; // COLOR//
  Tupla4f especularPuntual2 = {10.0,0.0,10.0,10.0};// BRILLO

  Tupla4f posicionPuntual3 = {0.0,0.0,1.0,0.0};// DESDE FRENTE
  Tupla4f difusaPuntual3 = {0.0,0.0,0.0,1.0}; //COLOR
  Tupla4f especularPuntual3 = {10.0,0.0,10.0,10.0};// BRILLLO

  Tupla4f posicionPuntual4 = {0.0,0.0,1.0,0.0};// DESDE ARRIBA
  Tupla4f difusaPuntual4 = {0.5,0.5,0.5,0.5};// COLOR
  Tupla4f especularPuntual4 = {10.0,0.0,10.0,10.0};// Brillo

  Luz* luzNoviembre= nullptr;
  Luz* luzPuntualMagenta = nullptr;
  Luz* luzPuntual2 = nullptr;
  Luz* luzPuntual3 =nullptr;
  Luz* luzPuntual4=nullptr;



  void clear_window();
	void dibujar_objeto_actual();

   // Transformación de cámara
	void change_projection( const float ratio_xy );
	void change_observer();


   public:

   Escena();
   ~Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
	void dibujar() ;

	// Interacción con la escena
 bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
 void teclaEspecial( int Tecla1, int x, int y );
 void conmutarAnimaciones();
 void siguienteParametro();
 void mgeDesocupado();


};
#endif
