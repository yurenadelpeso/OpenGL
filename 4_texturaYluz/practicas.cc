//**************************************************************************
// Prácticas
//
// F.J. melero
//
// GPL
//**************************************************************************


#include "aux.h" // includes de OpenGL, windows, y librería std de C++
#include "escena.h"

// variable que contiene un puntero a la escena
Escena *escena = nullptr ;
//int modoActual=0;
 

 //***************************************************************************
//GESTORA DEL EVENTO DESOCUPADO (IDLE EVENT)
// la funcion se llama periodicamente con las animaciones activadas
// actualiza el estado de los parametros del objeto jerarquico
//
// 
//***************************************************************************
void funcion_desocupado(){
   //objJerarquico->actualizarEstado();
   escena->mgeDesocupado();
   //glutPostRedisplay();
}


//***************************************************************************
// Funcion principal que redibuja la escena
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void draw_scene(void)
{
	if ( escena != nullptr )
      escena->dibujar();
	glutSwapBuffers();
   glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size( int newWidth, int newHeight )
{
	if ( escena != nullptr )
      escena->redimensionar(newWidth,newHeight);
	glutPostRedisplay();
}


//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys( unsigned char tecla, int x, int y )
{
	int salir = 0;

   if ( escena!= nullptr )
      salir = escena->teclaPulsada( tecla, x, y );

	if ( salir ){
		delete escena;
      escena = nullptr ;
		exit(0);
	}else
		glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys( int tecla, int x, int y )
{
	if (escena!=NULL)
	  escena->teclaEspecial( tecla, x, y );
	glutPostRedisplay();
}

//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main( int argc, char **argv )
{
   using namespace std ;

   
   escena = new Escena();// crear la escena (un puntero a la misma)
   glutInit( &argc, argv ); // Incialización de GLUT

   // se indica las caracteristicas que se desean para la visualización con OpenGL
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

   // variables que determninan la posicion y tamaño de la ventana X
   const int UI_window_pos_x  = 50,
             UI_window_pos_y  = 50,
             UI_window_width  = 500,
             UI_window_height = 500;

   // posicion de la esquina inferior izquierdad de la ventana
   glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

   // tamaño de la ventana (ancho y alto)
   glutInitWindowSize(UI_window_width,UI_window_height);

   // llamada para crear la ventana, indicando el titulo
   glutCreateWindow("Practica 4: Yurena del Peso");

   // asignación de la funcion llamada "dibujar" al evento de dibujo
   glutDisplayFunc( draw_scene );

   // asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
   glutReshapeFunc( change_window_size );

   // asignación de la funcion llamada "tecla_normal" al evento correspondiente
   glutKeyboardFunc( normal_keys );

   // asignación de la funcion llamada "tecla_Especial" al evento correspondiente
   glutSpecialFunc( special_keys );

   // inicialización de librería GLEW (solo en Linux)
   #ifdef LINUX
   const GLenum codigoError = glewInit();

   if ( codigoError != GLEW_OK ) // comprobar posibles errores
   {
      cout << "Imposible inicializar ’GLEW’, mensaje recibido: " << glewGetErrorString(codigoError) << endl ;
      exit(1) ;
   }
   #endif

   // funcion de inicialización de la escena (necesita que esté la ventana creada)
   escena->inicializar( UI_window_width, UI_window_height );

   // TEST

   // ejecutar del bucle de eventos
   glutMainLoop();

   return 0;
}
