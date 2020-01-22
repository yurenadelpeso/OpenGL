

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....
#include "jerarquico.h"
#include "luz.h"
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
    ply = new ObjPLY("plys/big_dodge.ply");
    plyrev = new ObjRevolucion("plys/peon.ply",num_instancias_perf);

    //p3
    objJerarquico=new ObjJerarquico();
   // OJ=new ObjJerarquico();

    // P4
    
    /*luzInfinita = new Luz(GL_LIGHT0, posicionDireccional, ambiente, difusaDireccional, especularDireccional);
    luzPuntualMagenta = new Luz(GL_LIGHT1, posicionPuntual, ambiente, difusaPuntual, especularPuntual);
    luzPuntual2 = new Luz(GL_LIGHT2, posicionPuntual2, ambiente, difusaPuntual2, especularPuntual2);
    */
    luzNoviembre = new Luz(GL_LIGHT0, posicionDireccional, ambiente, difusaDireccional, especularDireccional);    
    luzPuntualMagenta = new Luz(GL_LIGHT1, posicionPuntual, ambiente, difusaPuntual, especularPuntual);
    luzPuntual2 = new Luz(GL_LIGHT2, posicionPuntual2, ambiente, difusaPuntual2, especularPuntual2);

    luzPuntual3 = new Luz(GL_LIGHT3, posicionPuntual3, ambiente, difusaPuntual3, especularPuntual3);
    luzPuntual4 = new Luz(GL_LIGHT4, posicionPuntual4, ambiente, difusaPuntual4, especularPuntual4);



    // ESTOS PUNTOS DELIMIRAN LA PARTE DE LA IMAGEN QUE CONFIGURA EL CUADRO
    std::vector<Tupla2f> verticesCuadro = {
        { 0, 1 }, // 0
        { 0, 0 }, // 1
        { 1, 0 }, // 2
        { 1, 1 }, // 3
    };

//SELECCIONAR UNA PARTE DEL CUADRO
    std::vector<Tupla2f> VC = {
        { 0.25, 0.75 }, // 0
        { 0.25, 0.25 }, // 1
        { 0.75, 0.25 }, // 2
        { 0.75, 0.75 }, // 3
    };


     std::vector<Tupla2f> VC1 = {
        { 0, 1 }, // 0
        { 0, 0 }, // 1
        { 1, 0 }, // 2
        { 1, 1 }, // 3
    };

    cuadro = new Cuadro("./imagen2.jpg", verticesCuadro); 

    C= new OtroCuadro ("./imagen.jpg", VC);
    C1= new OtroCuadro ("./imagen.jpg", VC1);


    objeto_actual = 6;
    num_objetos = 10; // se usa al pulsar la tecla 'O' (rotar objeto actual)
    num_modos = 4;
    shadeModel = true;
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

	Width  = UI_window_width;
	Height = UI_window_height;

 
  glEnable(GL_LIGHTING); // Activar las luces de forma general 
  glShadeModel(GL_SMOOTH);// Activar por defecto el modo suave
  glEnable(GL_NORMALIZE); 

  cuadro->prepara_textura();
  C->prepara_textura();
  C1->prepara_textura();

  conmutarLuz=true;
  conmutarLuzPuntual=false;
  conmutarLuzPuntual3=false;
  conmutarLuzPuntual4=false;
  luzNoviembre->conmutar(conmutarLuz);
  luzPuntualMagenta->conmutar(conmutarLuz); 
  luzPuntual2->conmutar(conmutarLuzPuntual);
  luzPuntual3->conmutar(conmutarLuzPuntual3);
  luzPuntual4->conmutar(conmutarLuzPuntual4);


  change_projection( float(UI_window_width)/float(UI_window_height) );// DONDE SE INICIALIZA REALMENTE ESTO???
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
       // cout<<"entrando en case de lineas \n";   
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        ajedrez=0; 
       break ;

       case 1:
        //cout<<"entrando en case de relleno \n";     
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        ajedrez=0; 
       break ;

      case 2:
       //si quisiera poner un vertice de cada color deberia hacerlo aqui
        //cout<<"entrando en case de puntos \n";        
        glPointSize(4.0);
        glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
        ajedrez=0; 
      break ;

      case 3:
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        //cout<<"entrando en case de ajedrez \n";
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
        //cout<<"OBJETO ACTUAL "<<objeto_actual<<endl;
        cubo->draw(modo,ajedrez);
      }
    break ;

    case 1:
      if ( tetraedro != nullptr ){
        //cout<<"OBJETO ACTUAL "<<objeto_actual<<endl;
        tetraedro->draw(modo,ajedrez);
      }
    break ;
 
    case 2:
      if ( cilindro != nullptr ){
        //cout<<"OBJETO ACTUAL "<<objeto_actual<<endl;
        cilindro = new Cilindro(2, num_instancias_perf );
        cilindro->draw(modo, ajedrez);     
      }
    break ;

    case 3:
      if ( ply != nullptr ){
        //cout<<"entrando a PLY";
        ply->draw(modo, ajedrez);
      }
    break ;

    case 4:
     if ( plyrev != nullptr ){
      //cout<<"entrando a PLYREV \n";
      plyrev = new ObjRevolucion("./plys/peon.ply", num_instancias_perf );
      //cout << "num rev de mi objeto revolucion == " << num_instancias_perf << endl ;
      plyrev->draw(modo, ajedrez);
     }
    break ;

    case 5:
    //cout<<"OBJETO ACTUAL "<<objeto_actual;
     if ( cono != nullptr ){
        cono = new Cono(2,num_instancias_perf);
        //cout << "\n num rev de mi objeto revolucion == " << num_instancias_perf << endl ;
        cono->draw(modo, ajedrez);          
     }
    break ;

    case 6:
    //cout<<"OBJETO ACTUAL "<<objeto_actual;
     if ( esfera!= nullptr ){
      esfera = new Esfera(8, num_instancias_perf);
      //cout << " \n num rev de mi objeto revolucion == " << num_instancias_perf << endl ;
      esfera->draw(modo, ajedrez);
          
     }
    break ;
 
      
   case 7:
    if (cuadro != nullptr)
      //cout<<"entrando a CUADRO \n";
      modo=1;
      //cout << "num rev de mi objeto revolucion == " << num_instancias_perf << endl ;
      cuadro->draw(modo, ajedrez);
    break;
  case 8:
    if (C != nullptr)
     // cout<<"entrando a CUADRO \n";
      modo=1;
      C->draw(modo, ajedrez);
    break;
  case 9:
    if (C1 != nullptr)
      //cout<<"entrando a CUADRO \n";
      modo=1;
      C1->draw(modo, ajedrez);
    break;

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

void Escena::dibujar()  //glEnable(GL_NORMALIZE);
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); /* Conditional jump or move depends on uninitialised value(s)
*/// Limpiar la pantalla
	change_observer();
  ejes.draw();
  glEnable(GL_CULL_FACE) ;
  dibujar_objeto_actual();

  //luzNoviembre->conmutar(true); //ENCENDER LA LZ INFIMNITA
  //luzPuntualMagenta->conmutar(true);// Encender la luz direccional
 //luzPuntual2->conmutar(true);// Encender la luz direccional
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
    case 'H':
        // Modo suavizado
        if (shadeModel) {
            glShadeModel(GL_FLAT);
            shadeModel = !shadeModel;
            cout << "Modo suavizado GL_FLAT" << endl;
        } else {
            shadeModel = !shadeModel;
            glShadeModel(GL_SMOOTH);
            cout << "Modo suavizado GL_SMOOTH" << endl;
        }
        break;
     case 'U':
        if(modo==1) modo=0;
        else modo=1;
        
      break;
      case 'V' :

       cout<<"CASE LETRA V, CONMUTANDO LUCES \n";
       //cout<<"Valor de la boleana en la entrada<<  "<< conmutarLuz;
        conmutarLuz=!conmutarLuz;
        luzPuntualMagenta->conmutar(conmutarLuz);
        //cout<<"Valor de la boleana en la entrada<<  "<< conmutarLuz;

      break;
      case 'C' :

       cout<<"CASE LETRA C, CONMUTANDO LUCES \n";
       cout<<"Valor de la boleana en la entrada<<  "<< conmutarLuzPuntual;
        conmutarLuzPuntual=!conmutarLuzPuntual;
        luzPuntual2->conmutar(conmutarLuzPuntual);
        cout<<"Valor de la boleana en la entrada<<  "<< conmutarLuzPuntual;

      break;
       case 'e' :

       //cout<<"CASE LETRA C, CONMUTANDO LUCES \n";
       //cout<<"Valor de la boleana en la entrada<<  "<< conmutarLuzPuntual;
        conmutarLuzPuntual3=!conmutarLuzPuntual3;
        luzPuntual3->conmutar(conmutarLuzPuntual3);
       // cout<<"Valor de la boleana en la entrada<<  "<< conmutarLuzPuntual;

      break;
       case 'E' :

       //cout<<"CASE LETRA C, CONMUTANDO LUCES \n";
       //cout<<"Valor de la boleana en la entrada<<  "<< conmutarLuzPuntual;
        conmutarLuzPuntual4=!conmutarLuzPuntual4;
        luzPuntual4->conmutar(conmutarLuzPuntual4);
       // cout<<"Valor de la boleana en la entrada<<  "<< conmutarLuzPuntual;

      break;
      case 'G':
        // Desactivar/Activar luces
        if (glIsEnabled(GL_LIGHTING)) {
            glDisable(GL_LIGHTING);

            luz=false;
            cout << "VALOR DE LA VARIABLE LUZ == " << luz << endl ;
        } else {
            glEnable(GL_LIGHTING);
            luz=true;
            cout << "variable luz == " << luz << endl ;
        }
      break;
      
      case 'Q' :
         // salir
         return true ;
         break ;
      
      case 'O' :
         // activar siguiente objeto
         objeto_actual = (objeto_actual+1) % num_objetos ;
         //cout << "objeto actual == " << objeto_actual << endl ;
         break ;
      case 'o' :
     // activar siguiente objeto
        objeto_actual = (objeto_actual+1) % num_objetos ;
        //cout << "objeto actual == " << objeto_actual << endl ;
      break ;

      case 'M' :
          modeloActual=(modeloActual+1)% num_modos;
          break;

      case 'N':
       // cout<<"CASE LETRA N, AUMENTANDO REVOLUCIONES";
        num_instancias_perf=num_instancias_perf+6;
      break; 

      case 'B':
        //cout<<"CASE LETRA B, DISMINUCION REVOLUCIONES";
        num_instancias_perf=num_instancias_perf-6;
      break; 
      
      case 'P':
        cout<<"CASE LETRA P, SIGUIENTE PARAMETRO    ";
        objJerarquico->siguienteParametro();
      break; 

      case 'A':
       cout<<"CASE LETRA A, ANIMACIONES  ";
        conmutarAnimaciones();
      break; 

      case 'Z':
        cout<<"CASE LETRA Z, AUMENTANDO PARAMACT     ";
        objJerarquico->incrementaParamAct();
      break; 

      case 'K':
        cout<<"CASE LETRA K, decrementaParamAct ";
        objJerarquico->decrementaParamAct();
      break; 

      case '<':
        cout<<"CASE <, DISMINUYENDO REVOLUCIONES    ";
        objJerarquico->decelerar();
      break; 

      case '>':
        objJerarquico->acelerar();
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
   Width  = newWidth/10;
   Height = newHeight/10;
   change_projection( float(newHeight)/float(newWidth) );
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************


void Escena::conmutarAnimaciones(){
    animacion=!animacion;
    if(animacion){
      //objJerarquico->inicioAnimaciones();
      glutIdleFunc(funcion_desocupado);
    }else{
      glutIdleFunc(nullptr);
    }
  
}

void Escena::mgeDesocupado(){

  luzPuntualMagenta->rotar(5, 0,1,0);
  
  objJerarquico->actualizarEstado();
  glutPostRedisplay();
}

Escena::~Escena(){
  delete cubo;
  delete tetraedro;
  delete cilindro;
  delete ply;
  delete plyrev;
  delete cono;
  delete esfera;
  delete objJerarquico;
  delete cuadro;
  delete C;
  delete C1;
}
//0 direccional(solo hay que decir un punto) 1 podicional