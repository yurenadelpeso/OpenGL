

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
    Front_plane       = 0.1;
    Back_plane        = 2000.0;
    Observer_distance = 2.0;
    Observer_angle_x  = 0.0 ;
    Observer_angle_y  = 0.0 ;

    ejes.changeAxisSize( 5000 );

    // crear los objetos de las prácticas: Mallas o Jerárquicos....
    //OBJETOS DISPONIBLES
    
    cubo = new Cubo();
    tetraedro = new Tetraedro();
    cilindro = new Cilindro(2,num_instancias_perf);

    cono= new Cono(2,num_instancias_perf);
    esfera=new Esfera(8, num_instancias_perf);
    frontera=new Frontera(num_instancias_perf);
 
   
    objeto_actual = 0;
    //cubo,tetraedro, cilindro,ply,plyrevolucion
    num_objetos = 5; // se usa al pulsar la tecla 'O' (rotar objeto actual)
    num_modos = 4;
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer

	Width  = UI_window_width/10;
	Height = UI_window_height/10;

  change_projection( float(UI_window_width)/float(UI_window_height) );
	glViewport( 0, 0, UI_window_width, UI_window_height );
}




void Escena::dibujar_objeto_actual()
{
   using namespace std ;




/*********************************************************************************************************************
****************************************SEGUN LA VARIABLE selecionar ********************************************
******************************************UN TIPO DE MODELO...................................................
***********************************************************************************************************************/
      switch( modeloActual )
    {
       case 0:
        cout<<"entrando en case de lineas \n";   
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        ajedrez=0; 
       break ;

       case 1:
        cout<<"entrando en case de relleno \n";     
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        ajedrez=0; 
       break ;

      case 2:
       //si quisiera poner un vertice de cada color deberia hacerlo aqui
        cout<<"entrando en case de puntos \n";        
        glPointSize(4.0);
        glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
        ajedrez=0; 
      break ;

      case 3:
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        cout<<"entrando en case de ajedrez \n";
        ajedrez=true;
      break;
    
       default:
        cout << "MODO DE DIBUJADO NO SOPORTADO " << endl;
       break ;
     }




/*****************************************************************************
/*****************************************************************************
     ************************OBJETOS DISPONIBLES EN EL CATALOGO****************************************
     ***************************************************************************/


  switch( objeto_actual )
  {

    case 0:
     if ( cubo != nullptr ){
        cout<<"entrando "<<objeto_actual<<endl;    
        
        cubo->draw(modo,ajedrez);
     }
    break ;

    case 1:
      if ( tetraedro != nullptr ){
        cout<<"entrando "<<objeto_actual<<endl;    
   
        tetraedro->draw(modo,ajedrez);
     }
    break ;
 
    case 2:
     if ( cilindro != nullptr ){
          cout<<"entrando a CILINDRO "<<objeto_actual<<endl;          
          cilindro = new Cilindro(2, num_instancias_perf );
          cilindro->draw(modo, ajedrez);
          //float aux= cilindro->tamFrontera();
          //Frontera *frontera = new Frontera(aux);
         // frontera->draw(especial,especial);
          
     }
    break ;


    case 3:
    cout<<"OBJETO ACTUAL "<<objeto_actual<<endl;
     if ( cono != nullptr ){
          cout<<"entrando a CONO \n";
          cono = new Cono(2,num_instancias_perf);
          cout << "\n num rev de mi objeto revolucion == " << num_instancias_perf << endl ;
          cono->draw(modo, ajedrez);
          
     }
    break ;

    case 4:
    cout<<"OBJETO ACTUAL "<<objeto_actual<<endl;
     if ( esfera!= nullptr ){
          cout<<"entrando a ESFERA \n";     
          esfera = new Esfera(8, num_instancias_perf);
          cout << " \n num rev de mi objeto revolucion == " << num_instancias_perf << endl ;
          esfera->draw(modo, ajedrez);
          
     }
    break ;
 
    


   default:
   cout << "draw_object: el número de objeto actual (" << objeto_actual << ") es incorrecto." << endl ;
   break ;
   }
}

// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
  ejes.draw();
  glEnable(GL_CULL_FACE) ;
  //glEnable(GL_NORMALIZE);
	dibujar_objeto_actual();
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;
   cout << "Tecla pulsada: '" << tecla << "'" << endl;

   switch( tecla )
   {
      case 'Q' :     // salir
         return true ;
      break ;
      
      case 'O' :
         objeto_actual = (objeto_actual+1) % num_objetos ;
         cout << "objeto actual == " << objeto_actual << endl ;
      break ;
      
      case 'o' :
         objeto_actual = (objeto_actual+1) % num_objetos ;
         cout << "objeto actual == " << objeto_actual << endl ;
      break ;

      case 'M' : 
          modeloActual=(modeloActual+1)% num_modos;    
      break;

      case 'N':
        cout<<"CASE LETRA N, AUMENTANDO REVOLUCIONES";
        num_instancias_perf=num_instancias_perf+6;
      break; 

      case 'B':
        cout<<"CASE LETRA B, DISMINUCION REVOLUCIONES";
        num_instancias_perf=num_instancias_perf-6;
      break; 
      
     

       
   }
   return false ;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         Observer_angle_y-- ;
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y++ ;
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x-- ;
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x++ ;
         break;
	   case GLUT_KEY_PAGE_UP:
         Observer_distance *=1.2 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.2 ;
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wy = 0.84*Front_plane ,
   wx = ratio_xy*wy;
   glFrustum( -wx, +wx, -wy, +wy, Front_plane, Back_plane );
}
void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_x, 1.0 ,0.0, 0.0 );
   glRotatef( Observer_angle_y, 0.0, 1.0, 0.0 );
}

//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth;
   Height = newHeight;
   change_projection( float(newHeight)/float(newWidth) );
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************






Escena::~Escena(){
  delete cubo;
  delete tetraedro;
  delete cilindro;
  delete cono;
  delete esfera;



}
//0 direccional(solo hay que decir un punto) 1 podicional
