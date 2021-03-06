#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"





class Escena
{
   

   public:
   int  num_instancias_perf=20;
   bool ajedrez= false;
   int modo=0; // 0 para dibujar modo inmediato, 1 para dibujo diferido
   int modeloActual=0;

   

   
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
   Cubo * cubo = nullptr ; 
   Tetraedro *tetraedro = nullptr;
   Cilindro *cilindro =nullptr;
   Esfera *esfera=nullptr;
   Cono * cono=nullptr;
   Frontera *frontera=nullptr;
   
  

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



};
#endif
