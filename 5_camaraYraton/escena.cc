

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....
#include "jerarquico.h"
#include "luz.h"
#include "camara.h"
//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
    Front_plane       = 0.1;
    Back_plane        = 2000.0;
    Observer_distance = 2.0;
    //Observer_angle_x  = 0.0 ;
    //Observer_angle_y  = 0.0 ;


    ejes.changeAxisSize( 5000 );

    // crear los objetos de las prácticas: Mallas o Jerárquicos....
    //OBJETOS DISPONIBLES
    cubo = new Cubo();
    tetraedro = new Tetraedro();
    cilindro = new Cilindro(2,num_instancias_perf);
    cono= new Cono(2,num_instancias_perf);
    esfera=new Esfera(8, num_instancias_perf);
    //ply = new ObjPLY("plys/big_dodge.ply");
   // plyrevolucion = new ObjRevolucion("plys/peon.ply",num_instancias_perf);

    //p3
    //objJerarquico=new ObjJerarquico();

    // P4
    luzInfinita = new Luz(GL_LIGHT0, posicionDireccional, ambiente, difusaDireccional, especularDireccional);
    luzPuntualMagenta = new Luz(GL_LIGHT1, posicionPuntual, ambiente, difusaPuntual, especularPuntual);
    luzPuntual2 = new Luz(GL_LIGHT2, posicionPuntual2, ambiente, difusaPuntual2, especularPuntual2);
    
   
    std::vector<Tupla2f> verticesCuadro = {
        { 0, 1 }, // 0
        { 0, 0 }, // 1
        { 1, 0 }, // 2
        { 1, 1 }, // 3
    };
    /*
    cuadro = new Cuadro("./imagen2.jpg", verticesCuadro); 
    */
     //P5
    //PARAMETROS DE LAS CAMARAS==> (tipo Camara,?,?,distancia del observador a la escena)
    //tipo ,near far, zoom
    camaras[0] = new Camara(0, Front_plane, Back_plane, 20);
    camaras[1] = new Camara(1, 5, Back_plane, 20);
    camaras[2] = new Camara(1, 20, Back_plane, 20);

    objeto_actual = 5;
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

	//Width  = UI_window_width;
	//Height = UI_window_height;

 
  glEnable(GL_LIGHTING); // Activar las luces de forma general 
  redimensionar(UI_window_width, UI_window_height);

  glShadeModel(GL_SMOOTH);// Activar por defecto el modo suave
  glEnable(GL_NORMALIZE); 

  /*
  cuadro->prepara_textura();
  */
  luz=true;
  luzInfinita->conmutar(true); //ENCENDER LA LZ INFIMNITA
  luzPuntualMagenta->conmutar(true);// Encender la luz direccional
  //luzPuntual2->conmutar(true);// Encender la luz direccional

  //change_projection( float(UI_window_width)/float(UI_window_height) );// DONDE SE INICIALIZA REALMENTE ESTO???
	//glViewport( 0, 0, UI_window_width, UI_window_height );
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
       // cout<<"entrando en case de relleno \n";     
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        ajedrez=0; 
       break ;

      case 2:
       //si quisiera poner un vertice de cada color deberia hacerlo aqui
       // cout<<"entrando en case de puntos \n";        
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
************************OBJETOS DISPONIBLES EN EL CATALOGO********************
******************************************************************************/


  switch( objeto_actual )
  {

    case 0:
     if ( cubo != nullptr ){
        //cout<<"entrando CUBO \n"; 
        cubo->draw(modo,ajedrez);
     }
    break ;

    case 1:
      if ( tetraedro != nullptr ){
        //cout<<"entrando TETRAEDRO \n";
        tetraedro->draw(modo,ajedrez);
     }
    break ;
 
    case 2:
     if ( cilindro != nullptr ){
         // cout<<"entrando a CILINDRO \n";          
          cilindro->draw(modo, ajedrez);
          
     }
    break ;

    /*case 3:
     if ( plyrevolucion != nullptr ){
        cout<<"entrando a PLY";
        ply->draw(modo, ajedrez);
    }
    break ;

    case 4:
     if ( plyrevolucion != nullptr ){
  
        cout<<"entrando a PLYREV \n";
       // plyrevolucion = new ObjRevolucion("./plys/peon.ply", num_instancias_perf );
        cout << "num rev de mi objeto revolucion == " << num_instancias_perf << endl ;
        plyrevolucion->draw(modo, ajedrez);
     }
    break ;*/

    case 3:
    cout<<"OBJETO ACTUAL "<<objeto_actual;
     if ( cono != nullptr ){
          //cout<<"entrando a CONO \n";
          //cono = new Cono(2,num_instancias_perf);
           cono->draw(modo, ajedrez);
          
     }
    break ;

    case 4:
    cout<<"OBJETO ACTUAL "<<objeto_actual;
     if ( esfera!= nullptr ){
          //cout<<"entrando a ESFERA \n";     
          //esfera = new Esfera(8, num_instancias_perf);
          esfera->draw(modo, ajedrez);
          
     }
    break ;
 
  
    case 5:
      dibujarNormal();
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
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
  ejes.draw();
  glEnable(GL_CULL_FACE) ;
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
   cout << "Escena::teclaPulsada::Tecla pulsada: '" << tecla << "'" << endl;

   switch( tecla )
   {
    case 'H':
        // Modo suavizado
        if (sombra) {
            glShadeModel(GL_FLAT);
            sombra = !sombra;
            //cout << "Escena::teclaPulsada::Modo suavizado GL_FLAT" << endl;
        } else {
            sombra = !sombra;
            glShadeModel(GL_SMOOTH);
           // cout << "Escena::teclaPulsada::Modo suavizado GL_SMOOTH" << endl;
        }
        break;
     case 'U':
       
        usarDiferido=!usarDiferido;// CAMBIAR DE DIFERIDO A INMEDIATO
        //cout << "MODO  " <<modo<< "usarDiferido  "<<usarDiferido<< endl;

      break;

     case 'G':
        // Desactivar/Activar luces
        if (glIsEnabled(GL_LIGHTING)) {
            glDisable(GL_LIGHTING);

            luz=true;
            cout << "Escena::teclaPulsada::VALOR DE LA VARIABLE LUZ == " << luz << endl ;
        } else {
            glEnable(GL_LIGHTING);
            luz= false;
            cout << "Escena::teclaPulsada::variable luz == " << luz << endl ;
        }
        break;
          
          
      case 'Q' :
         // salir
         return true ;
         break ;


      case 'O' :
         // activar siguiente objeto
         objeto_actual = (objeto_actual+1) % num_objetos ;
         cout << "Escena::teclaPulsada::objeto actual == " << objeto_actual << endl ;
         break ;
          case 'o' :
         // activar siguiente objeto
         objeto_actual = (objeto_actual+1) % num_objetos ;
         cout << "Escena::teclaPulsada::objeto actual == " << objeto_actual << endl ;
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
      
      case 'P':
        cout<<"CASE LETRA P, SIGUIENTE PARAMETRO";
        //objJerarquico->siguienteParametro();
      break; 

      case 'A':
        cout<<"CASE LETRA A, ANIMACIONES";
        conmutarAnimaciones();
      break; 

      case 'Z':
        cout<<"CASE LETRA Z, AUMENTANDO PARAMACT";
        //objJerarquico->incrementaParamAct();
      break; 

      case 'K':
        cout<<"CASE LETRA K, decrementaParamAct ";
        //objJerarquico->decrementaParamAct();
      break; 

      case '<':
        cout<<"CASE <, AUMENTANDO REVOLUCIONES";
        //objJerarquico->decelerar();
      break; 

      case '>':
       // objJerarquico->acelerar();
      break;      
   }
   return false ;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
      case GLUT_KEY_PAGE_UP:
        camaras[camaraActiva]->zoom(1.2);
        break;
    case GLUT_KEY_PAGE_DOWN:
        camaras[camaraActiva]->zoom(-1.2);
        break;
    case GLUT_KEY_F1:
    std::cout<<"RECONOZCO F1";
        camaraActiva = 0;
        redimensionar(Width, Height);
        break;
    case GLUT_KEY_F2:
    std::cout<<"RECONOZCO F2";
        camaraActiva = 1;
        redimensionar(Width, Height);
        break;
  
    
	}

}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************


void Escena::change_projection( const float ratio_xy )
{
  // glMatrixMode( GL_PROJECTION );
   //glLoadIdentity();
  const float wy = 0.84 * Front_plane,
              wx = ratio_xy * wy;
    camaras[camaraActiva]->setProyeccion(wx, wy);
}
void Escena::change_observer()
{

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  camaras[camaraActiva]->setObservador();
}

//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
  Width = newWidth;
  Height = newHeight;
  change_projection(float(Width) / float(Height));
  glViewport(0, 0, Width, Height);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************



void Escena::conmutarAnimaciones(){
  if(objeto_actual==7) {
    animaciones=!animaciones;
    if(animaciones){
      //objJerarquico->inicioAnimaciones();
      glutIdleFunc(funcion_desocupado);
    }else{
      glutIdleFunc(nullptr);
    }
  }
  else std::cout<<"EL OBJETO ACTUAL NO ES JERARQUICO";
}

void Escena::mgeDesocupado(){
  luzPuntualMagenta->rotar(5, 0,1,0);
  //objJerarquico->actualizarEstado();
  glutPostRedisplay();
}
/*************************************************************************
************************************************
*******************/

void Escena::dibujaSeleccion()
{
   std::cout<<"Escena::dibujaSeleccion()";
    glDisable(GL_DITHER);
    glDisable(GL_LIGHTING);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
          glPushMatrix();
            switch(i*3+j){
                case 0: glColor3ub(colores[0][0],colores[0][1],colores[0][2]);break;
                case 1: glColor3ub(colores[1][0],colores[1][1],colores[1][2]);break;
                case 2: glColor3ub(colores[2][0],colores[2][1],colores[2][2]);break;
                case 3: glColor3ub(colores[3][0],colores[3][1],colores[3][2]);break;
            }
            glTranslatef(i*3.0,i*2,-j*3.0);
            switch(i*3+j){
                case 0: tetraedro->draw_seleccion(modo); break;
                case 1: cilindro->draw_seleccion(modo); break;
                case 2: esfera->draw_seleccion(modo); break;
                case 3: cono->draw_seleccion(modo); break;
            }
        glPopMatrix();
        }
    }
    
}

void Escena::pick(int x, int y){
    std::cout<<"Escena::PICK \n";
    GLubyte pixels[3];
    GLint viewport[4];
    bool lighting = false;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpiar la pantalla
    if (glIsEnabled(GL_LIGHTING)) {
        lighting = true;
    }
    
    dibujaSeleccion();
    glGetIntegerv(GL_VIEWPORT, viewport);
    
    glReadPixels(x, viewport[3]-y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixels);

    if (lighting) {
        glEnable(GL_LIGHTING);
    }

    for(int i = 0; i < 6; ++i){
        //std::cout << colores[i][0] << colores[i][1] << colores[i][2] << std::endl;
        if((int)pixels[0] == (int)colores[i][0] && (int)pixels[1] == (int)colores[i][1] && (int)pixels[2] == (int)colores[i][2]){
            switch(i){
            case 0: tetraedro->seleccionar(); break;
            case 1: cilindro->seleccionar(); break;
            case 2: esfera->seleccionar(); break;
            case 3: cono->seleccionar(); break;
            }
        }
    }
    //std::cout << (int)pixels[0] << (int)pixels[1] << (int)pixels[2] << std::endl;
    //std::cout << x << " " << y << std::endl;
}


void Escena::dibujarNormal()
{
  modo=0;
  std::cout<<"Escena::dibujarNormal() \n";
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
        glPushMatrix();
        glTranslatef(i*3.0,i*2,-j*3.0);
        switch(i*3+j){
            case 0: tetraedro->draw(modo, ajedrez); break;
            case 1: cilindro->draw(modo, ajedrez); break;
            case 2: esfera->draw(modo, ajedrez); break;
            case 3: cono->draw(modo, ajedrez); break;
        }
        glPopMatrix();
        }
    }
  
}
void Escena::clickRaton(int boton, int estado, int x, int y)
{
  std::cout<<"Escena::clickRaton \n";
    switch(boton){
        case GLUT_RIGHT_BUTTON:
            std::cout<<"CASE BOTON DERECHO\n";

            if (estado == GLUT_DOWN) {
                right_clicking = true;
                x_clickpos = x;
                y_clickpos = y;
            } else {
                right_clicking = false;
            }
            break;
        case GLUT_LEFT_BUTTON:
         std::cout<<"CASE BOTON IZQUIERDO \n";
            if (estado == GLUT_DOWN) {
                left_clicking = true;
                x_clickpos = x;
                y_clickpos = y;
                pick(x, y);
            } else left_clicking = false;
            break;
        case 3:
           std::cout<<"CASE 3 CAMARA \n";
            camaras[camaraActiva]->zoom(0.2);
            break;
        case 4:
         std::cout<<"CASE 4 CAMARA \n";
            camaras[camaraActiva]->zoom(-0.2);
            break;
        default:
            break;
    }
}

void Escena::ratonMovido(int x, int y)
{
   std::cout<<"Escena::ratonMovido";
    if (right_clicking) {
        yaw += x-x_clickpos;
        pitch -= y_clickpos-y;
        x_clickpos = x;
        y_clickpos = y;
        camaras[camaraActiva]->girar(pitch, yaw);
    }
    glutPostRedisplay();
}

//0 direccional(solo hay que decir un punto) 1 podicional