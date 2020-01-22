#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "jerarquico.h"
#include "luz.h"
#include "camara.h"
typedef int ModoVis;



class Escena
{
   

   public:
 
  int num_instancias_perf=20;
  bool ajedrez= false;
  bool usarDiferido=false;

   int modo=0; // 0 para dibujar modo inmediato, 1 para dibujo diferido

   int modeloActual=0;
   //p3
   bool animaciones;
   //p4
   bool luz=true;
   

   
   private:
   Ejes ejes;

/********************************************************************
 ***** variables que definen la posicion de la camara en coordenadas polares*/
   GLfloat Observer_distance;
   GLfloat Observer_angle_x;
   GLfloat Observer_angle_y;
/******************************************************************************
   ***variables que controlan la ventana y la transformacion de perspectiva*/
   GLfloat Width, Height, Front_plane, Back_plane;
   int objeto_actual, // OBJETO_ACTUAL objeto actual (el que se visualiza)
       num_objetos,  //NUM_OBJETOS: número de objetos(actualizado al crear los objetos en el constructor)  
       num_modos  ;

   

   /********************p2*********************
   ****************************/
   // Objetos de la escena es importante inicializarlo a 'nullptr'
   
   Cubo * cubo = nullptr ; 
   Tetraedro *tetraedro = nullptr;
   Cilindro *cilindro =nullptr;
   //ObjPLY * ply = nullptr;
   //ObjRevolucion * plyrevolucion= nullptr;
   Esfera *esfera=nullptr;
   Cono * cono=nullptr;
   /******************************************************************/


   /**********************p3**************************************
   **********************/
   //ObjJerarquico *objJerarquico=nullptr;
 


  /*********************** P4*****************************
  *************************************************************/
  // Cuadro* cuadro = nullptr;//para las texturas
   
  //para las luces
  bool sombra = true; 
  Tupla4f ambiente = {0.0,0.0,0.0,1.0};

  Tupla4f posicionDireccional = {0.0,0.0,1.0,0.0};
  Tupla4f difusaDireccional = {1.0,1.0,1.0,1.0};
  Tupla4f especularDireccional = {1.0,1.0,1.0,1.0};
  
  Tupla4f posicionPuntual = {10.0,0.0,0.0,1.0};
  Tupla4f difusaPuntual = {1.0,0.0,1.0,1.0};
  Tupla4f especularPuntual = {1.0,0.0,1.0,1.0};
  
  Tupla4f posicionPuntual2 = {0.0,1.0,0.0,0.0};
  Tupla4f difusaPuntual2 = {1.0,0.0,0.0,1.0};
  Tupla4f especularPuntual2 = {1.0,0.0,0.0,1.0};
  
  Luz* luzInfinita = nullptr;
  Luz* luzPuntualMagenta = nullptr;
  Luz* luzPuntual2 = nullptr;
/******************************************************************************/

/******************************************************************************
********************************p5***************************************/
//P5
    bool left_clicking = false, right_clicking = false;
    int x_clickpos = 0, y_clickpos = 0, yaw = 0, pitch = 0;
    Camara *camaras[3];
    int camaraActiva = 0;
    GLubyte colores[6][3] = { {255,100,100}, {230,50,50}, {210,50,100}, {180,80,80}, {140,80,80}, {100,80,80}};
/******************************************************************************/





  void clear_window();
	void dibujar_objeto_actual();

  // Transformación de cámara
	void change_projection( const float ratio_xy );
	void change_observer();


   public:

   Escena();
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
//P5
 void dibujaSeleccion();
 void pick(int x, int y);
 void dibujarNormal();
 void clickRaton(int boton, int estado, int x, int y);
 void ratonMovido(int x, int y);
};
#endif
