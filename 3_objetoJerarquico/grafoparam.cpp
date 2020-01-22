// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: GrafoParam.cc
// -- implementación del objeto jerárquico de la práctica 3
//
// ############################################################################

#include "grafoparam.h"

// -----------------------------------------------------------------------------
// constructor: crea mallas indexadas en los nodos terminales del grafo

GrafoParam::GrafoParam()
{
   cilindro = new Cilindro( 2, 16 );
   cubo     = new Cubo();
   esfera   = new Esfera(8,16);
   cono     = new Cono(2,16);
   cupula    = new Cupula(2,16);
   for( unsigned i = 0 ; i < num_parametros ; i++ ){
        movimientos.push_back(0.0);
    }
}
// -----------------------------------------------------------------------------

void GrafoParam::actualizarValorEfe( const unsigned iparam, const float valor_na )
{
   assert( iparam < num_parametros );
   
   using namespace std ;
   cout << "GrafoParam::actualizarValorEfe( " << iparam << ", " << valor_na << " )" << endl ;


   switch( iparam )
   {
     // std::cout<<"entrado en actualizacion de valores: \n";
      case 0:
        extenderCanyon=valor_na*0.2;
        std::cout<<"entrado en actualizacion de valores 0 \n";
      
      break ;
      case 1:
        rotarcilindro=valor_na*10;
        std::cout<<"entrado en actualizacion de valores 1 \n";
      break ;

      case 2:
        rotarcanyon=valor_na*10;//rota la cupula
        std::cout<<"entrado en actualizacion de valores 2 \n";
         break ;
      case 3:
        canyonArriba=valor_na;
        std::cout<<"entrado en actualizacion de valores 3 \n"; 
      break ;

      case 4:
        abrirTapa=valor_na*210;
        std::cout<<"entrado en actualizacion de valores 4 \n";
       
       break ;
      case 5:
        rotarTapa=valor_na*20;
        std::cout<<"entrado en actualizacion de valores 5 \n";
       break ;
      case 6:
        avanzarTanque=valor_na;
        rotarRuedasA=valor_na*(2.0 * M_PI * 8);//radio rueda 1.25
        std::cout<<"entrado en actualizacion de valores 6 \n";
      break ;
      case 7:
        rotarExtremo=valor_na*20;
        std::cout<<"entrado en actualizacion de valores 7  \n";
      break ;
      default:
        movimientos[iparam] = valor_na*50;
      break;
   }
}
















































// -----------------------------------------------------------------------------
// visualización del objeto Jerárquico con OpenGL,
// mediante llamadas a los métodos 'draw' de los sub-objetos

void GrafoParam::draw( const int p_modo_vis, const bool p_usar_diferido )
{
   // asegurarnos que está inicializado ok
  assert( cono     != nullptr );
  assert( cubo     != nullptr );
  assert( cilindro != nullptr );
  assert( esfera != nullptr );
  assert( cupula != nullptr );

  modo_vis      = p_modo_vis;
  usar_diferido = p_usar_diferido ;
  miDibujo(modo_vis,usar_diferido); 
  //dibujoExamen(modo_vis,usar_diferido);

}





/*
*
*
*DIBUJO DE LA TANQUETA
*
*/
void GrafoParam::dibujoExamen(const int p_modo_vis, const bool p_usar_diferido){


  glPushMatrix();
    ruedaTanqueta( modo_vis, usar_diferido );
    //tanqueta(p_modo_vis, p_usar_diferido);
  glPopMatrix();
}


void GrafoParam::ruedaTanqueta(const int modo_vis, const bool usar_diferido){
    glPushMatrix();
     // glRotatef(moverRuedaTanqueta,0,0,1);
      glRotatef(90,1,0,0);
      glScalef(0.5,0.5,0.5);
      cilindro->draw( modo_vis, usar_diferido );
   glPopMatrix();
}



























/*
*
*DIBUJO DEL TANQUE
*
*
*/
void GrafoParam::miDibujo(const int p_modo_vis, const bool p_usar_diferido){ 

  glPushMatrix();
    std::cout<<"avanzar "<<avanzarTanque<<std::endl;
    glTranslatef(-avanzarTanque,0,0);
    glRotatef(rotarcilindro,0,1,0);
    std::cout<<"valor de rotar ciliindro ="<<rotarcilindro<<std::endl;
    tanque(p_modo_vis,p_usar_diferido);
   glPopMatrix();
}

void GrafoParam::cuatroRuedas(const int modo_vis, const bool usar_diferido){
    glPushMatrix();
      glPushMatrix();
       glTranslatef(0,0,2.5);
         parRueda(modo_vis, usar_diferido);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0,0,-2.5);
         parRueda(modo_vis, usar_diferido);
      glPopMatrix();  
   glPopMatrix();
}
void GrafoParam::parRueda(const int modo_vis, const bool usar_diferido){
    glPushMatrix();
      glPushMatrix();
         glTranslatef(-3,0,0);
         rueda(modo_vis,usar_diferido);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(3,0,0);
         rueda(modo_vis,usar_diferido);
      glPopMatrix();
   glPopMatrix();
}


void GrafoParam::rueda(const int modo_vis, const bool usar_diferido){
    glPushMatrix();
      glRotatef(rotarRuedasA,0,0,1);
      glRotatef(90,1,0,0);
      glScalef(4,1,4);
      cilindro->draw( modo_vis, usar_diferido );
   glPopMatrix();
}
void GrafoParam::cuerpoBajo(const int modo_vis, const bool usar_diferido){
   glPushMatrix();
      cuatroRuedas(modo_vis,usar_diferido);
      glTranslatef(0,1.8,0);
      glScalef(8,2.5,4);
      cubo->draw( modo_vis, usar_diferido );
   glPopMatrix();
} 

void GrafoParam::cuerpoAlto(const int modo_vis, const bool usar_diferido){
    glPushMatrix();  
      glPushMatrix();
        glRotatef(rotarcanyon,0,1,0);
        glTranslatef(0,0.5,0);
        capsula(modo_vis, usar_diferido);
      glPopMatrix();  
      glScalef(1,0.5,1);
      cubo->draw( modo_vis, usar_diferido );
   glPopMatrix();
}

void GrafoParam::capsula(const int modo_vis, const bool usar_diferido){
    glPushMatrix();
      tapa(modo_vis, usar_diferido);
      glPushMatrix();
      glRotatef(canyonArriba,0,0,1);
      canyon(modo_vis, usar_diferido);
      glPopMatrix();
      glScalef(1,0.5,1);
      cilindro->draw( modo_vis, usar_diferido );
   glPopMatrix();

}

void GrafoParam::tapa(const int modo_vis, const bool usar_diferido){
   //cilindro radio 1,h=4
    glPushMatrix();
      glRotatef(rotarTapa,0,1,0);
      glTranslatef(0 ,0.25,0);
      glRotatef(180,1,0,0);
      glRotatef(abrirTapa,0,0,1);
      glScalef(0.40,0.40,0.40);//el diametro de las ruedas es 4
      cupula->draw( modo_vis, usar_diferido );
   glPopMatrix();

}

void GrafoParam::canyon(const int modo_vis, const bool usar_diferido){
    glPushMatrix();
      glPushMatrix();
        glTranslatef(extenderCanyon,0,0);
        glRotatef(rotarExtremo,1,0,0);
        canyonExtensible(modo_vis,usar_diferido);
      glPopMatrix();
      glTranslatef(-0.65,0,0);
      glRotatef(90,0,0,1);
      glScalef(0.40,0.40,0.40);
      cilindro->draw( modo_vis, usar_diferido );
   glPopMatrix();
}

void GrafoParam::pala(const int modo_vis, const bool usar_diferido){
    glPushMatrix();
      //glTranslatef(-1,0,0);
      glRotatef(90,1,0,0);
      //glScalef(0.5,0.5,0.5);
      cilindro->draw( modo_vis, usar_diferido );
   glPopMatrix();
}

void GrafoParam::canyonExtensible(const int modo_vis, const bool usar_diferido){
    glPushMatrix();
      glTranslatef(-1,0,0);
      glRotatef(90,0,0,1);
      glScalef(0.5,0.5,0.5);
      cilindro->draw( modo_vis, usar_diferido );
   glPopMatrix();
}


void GrafoParam::tanque(const int modo_vis, const bool usar_diferido){
   glPushMatrix();
    glPushMatrix();
    
      glTranslatef(0,3.5,0);
      glScalef(2.5,2.5,2.5);
      cuerpoAlto(modo_vis,usar_diferido);
    glPopMatrix();
    cuerpoBajo(modo_vis,usar_diferido);
  glPopMatrix();
}


void GrafoParam::miDibujo1(const int p_modo_vis, const bool p_usar_diferido){  
    glPushMatrix();
 
      glColor3f( 0.6, 0.2, 0.0 );
      glColor3f( 0.8, 0.3, 0.3 );

      glRotatef(45.0,0.0,1.0,0.0);
      glRotatef(45.0,0.0,0.0,1.0);
      glRotatef(45.0,1.0,0.0,0.0);
      
      cilindro->draw(p_modo_vis, p_usar_diferido );
      
   glPopMatrix();
}
/*
void GrafoParam::miDibujo2(const int p_modo_vis, const bool p_usar_diferido){  
    glPushMatrix();
 
      glColor3f( 0.6, 0.2, 0.0 );
      glColor3f( 0.8, 0.3, 0.3 );

      glTranslatef(0.0,130.0,0.0);
      glRotatef(45.0,0.0,1.0,0.0);
      glRotatef(45.0,0.0,0.0,1.0);
      glRotatef(45.0,1.0,0.0,0.0);
    
      
      cilindro->draw(modo_vis, usar_diferido );
      
   glPopMatrix();
}
void GrafoParam:: miDibujo3(const int p_modo_vis, const bool p_usar_diferido){
  int a=p_modo_vis;
   bool b=p_usar_diferido; 
    glPushMatrix();
      glColor3f( 0.8, 0.3, 0.3 );

    //palaGrande(a,b);
    glPopMatrix();
}
void GrafoParam::palaGrande(const int p_modo_vis, const bool p_usar_diferido){
        glPushMatrix();
          glTranslatef(-0.1,-1.3,0);
          glRotatef(anguloPala, 0, 0, 1);
          glTranslatef(-0.5,0,0);
          glRotatef(-90, 1, 0, 0);
          pala->draw(p_modo_vis,p_usar_diferido);
        glPopMatrix();

}

void GrafoParam::miDibujo4(const int p_modo_vis, const bool p_usar_diferido){ 
   int a=p_modo_vis;
   bool b=p_usar_diferido; 
    glPushMatrix();
      glColor3f( 0.8, 0.3, 0.3 );


      nuevoCuerpo(a,b);
     // nuevaPata_0(a,b);
      //nuevaPata_1(a,b);
       // nuevaPata_2(a,b);
        //nuevaPata_3(a,b);
   // nuevaAranya(a,b);
     //cuerpo(a,b);
    // abdomen1(a,b);
   //cabeza(a,b);
  //ojo(a,b);
      //tanque(a,b);
     // parRueda(a,b);
     // cuatroRuedas(a,b); 
    //pinza(a,b);
     //extremoPinza(a,b);
       
   glPopMatrix();
}

*/
/*
*
*nueva araña
*/

/*
void GrafoParam::nuevaPataCompleta(const int modo_vis, const bool usar_diferido){
  glPushMatrix();
  nuevaPata_3(modo_vis,usar_diferido);
  nuevaPata_2(modo_vis,usar_diferido);
  nuevaPata_1(modo_vis,usar_diferido);
  nuevaPata_0(modo_vis,usar_diferido);
  glPopMatrix();
}

void GrafoParam::nuevaPata_3(const int modo_vis, const bool usar_diferido){
   //cilindro radio 1,h=4
    glPushMatrix();
    glPushMatrix();
      glTranslatef(0,-10,31.5);
      glRotatef(180,1,0,0);
      glScalef(0.02,0.02,0.02);
      cono->draw(modo_vis,usar_diferido);
    glPopMatrix();
      glTranslatef(0,-4.5,31.5);
      //glRotatef(100,1,0,0);
      glScalef(1,2.5,0.75);
      cilindro->draw( modo_vis, usar_diferido );
   glPopMatrix();
}

void GrafoParam::nuevaPata_2(const int modo_vis, const bool usar_diferido){
   //cilindro radio 1,h=4
    glPushMatrix();
      glTranslatef(0,3,22);
      glRotatef(105,1,0,0);
      glScalef(1,5,0.75);
      cilindro->draw( modo_vis, usar_diferido );
   glPopMatrix();
}

void GrafoParam::nuevaPata_1(const int modo_vis, const bool usar_diferido){
   //cilindro radio 1,h=4
    glPushMatrix();
      glTranslatef(0,0,11.5);
      glRotatef(15,1,0,0);
      glScalef(1,2.8,0.75);
      cilindro->draw( modo_vis, usar_diferido );
   glPopMatrix();
}




void GrafoParam::nuevaPata_0(const int modo_vis, const bool usar_diferido){
   //cilindro radio 1,h=4
    glPushMatrix();
      glTranslatef(0,-5.7,6.5);
      glRotatef(90,1,0,0);
      glScalef(1,2,0.75);
      cilindro->draw( modo_vis, usar_diferido );
   glPopMatrix();
}

void GrafoParam::nuevaAranya(const int modo_vis, const bool usar_diferido){
   //cilindro radio 1,h=4
   glPushMatrix();       
      nuevoCuerpo(modo_vis,usar_diferido);
      /*glPushMatrix();
        glRotatef(movimientoAbdomen,0,0,1);
        abdomen(modo_vis, usar_diferido );
      glPopMatrix();
      cabeza(modo_vis, usar_diferido );
     
   glPopMatrix();
}
void GrafoParam::nuevoCuerpo(const int modo_vis, const bool usar_diferido){
   //cilindro radio 1,h=4
    glPushMatrix();

         glPushMatrix();//PATAX
         glRotatef(25+pata25X,0,1,0);
           glPushMatrix();
             glTranslatef(-4,0,0);
             glRotatef(25,0,1,0);
             glRotatef(180,0,1,0);
             nuevaPataCompleta(modo_vis, usar_diferido );
          glPopMatrix();
      glPopMatrix();
     


     glPushMatrix();//PATAY
     glRotatef(10+pata10Y,0,1,0);
      glPushMatrix();
        glRotatef(10,0,1,0);
         glTranslatef(-1,0,0);
         glRotatef(180,0,1,0);
         nuevaPataCompleta(modo_vis, usar_diferido );
      glPopMatrix();
    glPopMatrix();
     
      glPushMatrix();//PATAX
      glRotatef(-10+pata10X,0,1,0);
      glPushMatrix();
         glRotatef(-10,0,1,0);
         glRotatef(180,0,1,0);
         glTranslatef(-1,0,0);
         nuevaPataCompleta(modo_vis, usar_diferido );
      glPopMatrix();
     glPopMatrix();
     

      glPushMatrix();//PATAY  
      glRotatef(-25+pata25Y,0,1,0);
      glPushMatrix();
         glRotatef(-25,0,1,0);
         glRotatef(180,0,1,0);
         glTranslatef(-4,0,0);
         nuevaPataCompleta(modo_vis, usar_diferido );
      glPopMatrix();
      glPopMatrix();
      



      glPushMatrix();//PATAY
       glRotatef(-4+pata25Y,0,1,0);
       glPushMatrix();
       glTranslatef(-4,0,0);
       glRotatef(-25,0,1,0);
       nuevaPataCompleta(modo_vis, usar_diferido );
      glPopMatrix();
      glPopMatrix();
     
     glPushMatrix();//PATAX
     glRotatef(-10+pata10X,0,1,0);
     glPushMatrix();
        glRotatef(-10,0,1,0);
         glTranslatef(-1,0,0);
         nuevaPataCompleta(modo_vis, usar_diferido );
      glPopMatrix();
     glPopMatrix();




      glPushMatrix();//PATAY
      glRotatef(10+pata10Y,0,1,0);
      glPushMatrix();
         glRotatef(10,0,1,0);
         glTranslatef(1,0,0);
         nuevaPataCompleta(modo_vis, usar_diferido );
      glPopMatrix();
      glPopMatrix();
     
      glPushMatrix();//PATAX
         glRotatef(25+pata25X,0,1,0);
         glTranslatef(4,0,0);
         glRotatef(25,0,1,0);
         nuevaPataCompleta(modo_vis, usar_diferido );
      glPopMatrix();
      glPopMatrix();

    //aqui le pongo matrix??
         glScalef(13,6,10);
         glScalef(0.02,0.02,0.02);//el diametro de las ruedas es 4
         esfera->draw( modo_vis, usar_diferido );

   glPopMatrix();

}
*/


/*
* primera araña
**/
/*
void GrafoParam::aranya(const int modo_vis, const bool usar_diferido){
   //cilindro radio 1,h=4
   glPushMatrix();       
      cuerpo(modo_vis,usar_diferido);
      glPushMatrix();
        glRotatef(movimientoAbdomen,0,0,1);
        abdomen(modo_vis, usar_diferido );
      glPopMatrix();
      cabeza(modo_vis, usar_diferido );
     
   glPopMatrix();
}

void GrafoParam::extremoPinza(const int modo_vis, const bool usar_diferido){
   glPushMatrix();
      glPushMatrix();
      glTranslatef(1,-0.5,0);
      glRotatef(105,0,0,-1);
      glScalef(0.5,0.75,0.5);//el diametro de las ruedas es 4
        cilindro->draw( modo_vis, usar_diferido );
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0.5,-1.5,0);
         glRotatef(145,0,0,-1);
         glScalef(0.5,0.75,0.5);//el diametro de las ruedas es 4
         cilindro->draw( modo_vis, usar_diferido );
      glPopMatrix();
   glPopMatrix();
}

void GrafoParam::pinza(const int modo_vis, const bool usar_diferido){
   glPushMatrix();
      glPushMatrix();     
         glPushMatrix();
            glPushMatrix();
               glRotatef(22,0,0,-1);
               //glRotatef(45,0,1,0);
                //glRotatef(45,1,0,0);
            glTranslatef(8,-5.5,0);
               extremoPinza(modo_vis, usar_diferido);
            glPopMatrix();
            glTranslatef(3,-4.2,0);
            glRotatef(10,0,0,1);
            glScalef(0.75,2,0.75);//el diametro de las ruedas es 4
            cilindro->draw( modo_vis, usar_diferido );
         glPopMatrix();
      glPopMatrix();
      glPushMatrix();
         glRotatef(55,0,0,1);
         glScalef(1,1.5,1);//el diametro de las ruedas es 4
         cilindro->draw( modo_vis, usar_diferido );
      glPopMatrix();
   glPopMatrix();


    
   glPopMatrix();
}
void GrafoParam::pata_0(const int modo_vis, const bool usar_diferido){
   //cilindro radio 1,h=4
    glPushMatrix();
      glTranslatef(3,-3.5,0);
      glRotatef(90,0,0,1);
      glScalef(0.5,0.75,0.5);//el diametro de las ruedas es 4
      cilindro->draw( modo_vis, usar_diferido );
   glPopMatrix();
}

void GrafoParam::pata_1(const int modo_vis, const bool usar_diferido){
   //cilindro radio 1,h=4
    glPushMatrix();
      glPushMatrix();
         pata_0(modo_vis, usar_diferido);
      glPopMatrix();
      glRotatef(30,0,0,1);
      glScalef(0.75,2,0.75);//el diametro de las ruedas es 4
      cilindro->draw( modo_vis, usar_diferido );
   glPopMatrix();
}


void GrafoParam::pata_2(const int modo_vis, const bool usar_diferido){
   //cilindro radio 1,h=4
    glPushMatrix();
      glPushMatrix();
       glTranslatef(3.5,-4.2,0);
      pata_1(modo_vis, usar_diferido);
     glPopMatrix();
      glRotatef(55,0,0,1);
      glScalef(1,1.5,1);//el diametro de las ruedas es 4
      cilindro->draw( modo_vis, usar_diferido );
   glPopMatrix();
}


void GrafoParam::pata_3(const int modo_vis, const bool usar_diferido){
   //cilindro radio 1,h=4
    glPushMatrix();
      glPushMatrix();
      glTranslatef(3.5,-2,0);
         pata_2(modo_vis, usar_diferido);
      glPopMatrix();
      glRotatef(70,0,0,1);
      glScalef(1.2,1,1.2);//el diametro de las ruedas es 4
      cilindro->draw( modo_vis, usar_diferido );
   glPopMatrix();
}
void GrafoParam::pata_completa(const int modo_vis, const bool usar_diferido){
   //cilindro radio 1,h=4
    glPushMatrix();
      glPushMatrix();
       glTranslatef(3.5,0,0);
         pata_3(modo_vis, usar_diferido);
      glPopMatrix();
      glRotatef(100,0,0,1);
      glScalef(1.5,1.5,1.5);//el diametro de las ruedas es 4
      cilindro->draw( modo_vis, usar_diferido );
   glPopMatrix();
}
void GrafoParam::abdomen(const int modo_vis, const bool usar_diferido){
   glPushMatrix();
   //PODER MOVER HASTA 17
   glRotatef(-10,0,0,1);
   glTranslatef(-20,0,0);
    glScalef(14,7.5,12);
    glScalef(0.02,0.02,0.02);//el diametro de las ruedas es 4
    esfera->draw( modo_vis, usar_diferido );
   glPopMatrix();
}



void GrafoParam::abdomen1(const int modo_vis, const bool usar_diferido){
   glPushMatrix();
   //PODER MOVER HASTA 17
      glScalef(0.2,0.2,0.2);//el diametro de las ruedas es 4

    cono->draw( modo_vis, usar_diferido );
   glPopMatrix();
}
void GrafoParam::cabeza(const int modo_vis, const bool usar_diferido){
   glPushMatrix();

      glPushMatrix();
         glRotatef(-26,0,1,0);
         glTranslatef(23,2.2,-1.9); 
         glScalef(0.5,1.2,1);
         ojo( modo_vis, usar_diferido );
      glPopMatrix();

      glPushMatrix();
         glRotatef(-20,0,1,0);
         glTranslatef(24,1.6,-2.5); 
         glScalef(0.5,1.6,1.6);
         ojo( modo_vis, usar_diferido );
      glPopMatrix();


    glPushMatrix();
         glRotatef(16,0,1,0);
         glTranslatef(23,2.2,-1.9); 
         glScalef(0.5,1.2,1);
         ojo( modo_vis, usar_diferido );
      glPopMatrix();

      glPushMatrix();
         glRotatef(8,0,1,0);
         glTranslatef(24,1.6,-2.5); 
         glScalef(0.5,1.6,1.6);
         ojo( modo_vis, usar_diferido );
      glPopMatrix();

      glPushMatrix();
         glTranslatef(25,1,-2.3); 
         glScalef(0.5,2,2);
         ojo( modo_vis, usar_diferido );
      glPopMatrix();
      
      glPushMatrix();
         glTranslatef(25,1,2.3); 
         glScalef(0.5,2,2);
         ojo( modo_vis, usar_diferido );
     glPopMatrix();

      glTranslatef(19,0,0);
      glScalef(6,5,9);
      glScalef(0.02,0.02,0.02);//el diametro de las ruedas es 4
      esfera->draw( modo_vis, usar_diferido );
   glPopMatrix();
}
void GrafoParam::ojo(const int modo_vis, const bool usar_diferido){
    glPushMatrix();
      glScalef(0.02,0.02,0.02);//el diametro de las ruedas es 4
      esfera->draw( modo_vis, usar_diferido );
   glPopMatrix();
}

void GrafoParam::cuerpo(const int modo_vis, const bool usar_diferido){
   //cilindro radio 1,h=4
    glPushMatrix();
     glPushMatrix();
         glRotatef(120,0,1,0);
         glTranslatef(13,0,0);
         pata_completa(modo_vis, usar_diferido );
      glPopMatrix();
     glPushMatrix();
         glRotatef(90,0,1,0);
         glTranslatef(13,0,0);
         pata_completa(modo_vis, usar_diferido );
      glPopMatrix();
      glPushMatrix();
         glRotatef(65,0,1,0);
         glTranslatef(13,0,0);
         pata_completa(modo_vis, usar_diferido );
      glPopMatrix();
      glPushMatrix();
         glRotatef(40,0,1,0);
         glTranslatef(13,0,0);
         pata_completa(modo_vis, usar_diferido );
      glPopMatrix();
      glPushMatrix();
         glRotatef(-120,0,1,0);
         glTranslatef(13,0,0);
         pata_completa(modo_vis, usar_diferido );
      glPopMatrix();
     
     glPushMatrix();
         glRotatef(-90,0,1,0);
         glTranslatef(13,0,0);
         pata_completa(modo_vis, usar_diferido );
      glPopMatrix();
      glPushMatrix();
         glRotatef(-65,0,1,0);
         glTranslatef(13,0,0);
         pata_completa(modo_vis, usar_diferido );
      glPopMatrix();
      glPushMatrix();
         glRotatef(-40,0,1,0);
         glTranslatef(13,0,0);
         pata_completa(modo_vis, usar_diferido );
      glPopMatrix();

    //aqui le pongo matrix??
         glScalef(13,6,10);
         glScalef(0.02,0.02,0.02);//el diametro de las ruedas es 4
         esfera->draw( modo_vis, usar_diferido );

   glPopMatrix();

}

*/








