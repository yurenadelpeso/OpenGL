
// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: jerarquico.cc
// -- implementación del objeto jerárquico de la práctica 3
//
// #############################################################################

#include <chrono>

#include "jerarquico.h"

// -----------------------------------------------------------------------------

ObjJerarquico::ObjJerarquico()
{
   objparam = new GrafoParam();

   for( unsigned i = 0 ; i < objparam->numParametros() ; i++ )
   {
      valores_na.push_back( 0.0 );
      delta_valores.push_back( 1.0 );
      objparam->actualizarValorEfe( i, valores_na[i] ) ;
   }
   titulo_valores_na.push_back("0 extenderCanyon ");
   titulo_valores_na.push_back("1 rotarTanque EN EL EJE Y");
   titulo_valores_na.push_back("2 rotarCupula EN EL EJE Y");
   titulo_valores_na.push_back("3 rotarcanyon z");
   titulo_valores_na.push_back("4 ABRIR TAPA");
   titulo_valores_na.push_back("5 rotar tapa en eje y");
   titulo_valores_na.push_back("6 ANDAR EN EL PLANO X");
   titulo_valores_na.push_back("7 ROTAR EXTREMO DEL CAÑON");


}

// -----------------------------------------------------------------------------
// visualización del objeto Jerárquico con OpenGL,
// mediante llamadas a los métodos 'draw' del objeto

void ObjJerarquico::draw(  int modo_draw,  bool ajedrez  )
{
   assert( objparam != nullptr );
   objparam->draw( modo_draw, ajedrez);
}

float min(float a,float b){
   if(a<=b) return a;
   else return b;
}
float max(float a,float b){
   if(a>=b) return a;
   else return b;
}


void ObjJerarquico::incrementaParam(unsigned n_param)
{
   using namespace std ;
   assert( objparam != nullptr );
   assert( n_param < objparam->numParametros() );
  
  // cout<<"valor de na = "<<valores_na[n_param]<<endl;
   objparam->actualizarValorEfe( n_param, valores_na[n_param] );
   
}

void ObjJerarquico::decrementaParam(unsigned n_param)
{
   using namespace std ;
   assert( objparam != nullptr );
   assert( n_param < objparam->numParametros() );

 
   valores_na[n_param] -= delta_valores[n_param] ;
   objparam->actualizarValorEfe( n_param, valores_na[n_param] );
}

void ObjJerarquico::aceleraParam(unsigned n_param)
{
   using namespace std ;
   delta_valores[n_param] += 0.2 ;
  // cout << "Acelerado, delta == " << delta_valores[n_param] << endl ;
}

void ObjJerarquico::deceleraParam(unsigned n_param)
{
   using namespace std ;
   delta_valores[n_param] = std::max( delta_valores[n_param]-0.2, 0.2 ) ;
   //cout << "Decelerado, delta == " << delta_valores[n_param] << endl ;
}


// -----------------------------------------------------------------------------
// incrementa el parámetro actual



void ObjJerarquico::incrementaParamAct()
{
   using namespace std ;
   assert( objparam != nullptr );
   assert( i_param_act < objparam->numParametros() );
  switch(i_param_act){
     case 0://EXTENDER EL EXTREMO DEL CAÑON
     //DUDAS SOBRE LOS PARAMETROS DE ACELERACIÓN 
     
      //valores_na[i_param_act] =min(0.02,valores_na[i_param_act] += delta_valores[i_param_act]/20 );
      valores_na[i_param_act] = min(0,valores_na[i_param_act]+=delta_valores[i_param_act]);

      case 3://ROTAR CAÑON
         valores_na[i_param_act]= min(9,valores_na[i_param_act] += delta_valores[i_param_act]);
         break;
     
       case 4://ABRIR TAPA
         valores_na[i_param_act]= min(0.4,valores_na[i_param_act] += delta_valores[i_param_act]/20);
      break;

      default:
         valores_na[i_param_act] += delta_valores[i_param_act]/20 ;
      break;
   }
   //valores_na[i_param_act] += delta_valores_na/20.0 ;
   objparam->actualizarValorEfe( i_param_act, valores_na[i_param_act] );
}

// -----------------------------------------------------------------------------
// decrementa el parámetro actual

void ObjJerarquico::decrementaParamAct()
{
   using namespace std ;
   assert( objparam != nullptr );
   assert( i_param_act < objparam->numParametros() );
    switch(i_param_act){
      case 0:
         valores_na[i_param_act]=max(0, valores_na[i_param_act]-= delta_valores[i_param_act]/20) ;
      break;

      case 3:
            valores_na[i_param_act]= max(-9,valores_na[i_param_act] -= delta_valores[i_param_act]);
      break;
     
     case 4:
         valores_na[i_param_act]= max(0,valores_na[i_param_act] -= delta_valores[i_param_act]/20);
      break;
      default:
         valores_na[i_param_act] -= delta_valores[i_param_act]/20 ;
      break;
   }
   //valores_na[i_param_act] -= delta_valores_na/20.0 ;
   objparam->actualizarValorEfe( i_param_act, valores_na[i_param_act] );
}

// -----------------------------------------------------------------------------
// hacer que el parámetro actual sea el siguiente

void ObjJerarquico::siguienteParametro()
{
   using namespace std ;
   assert( objparam != nullptr );
   assert( i_param_act < objparam->numParametros() );

   i_param_act = (i_param_act+1) % objparam->numParametros();
   cout << "\nPARAMETRO ACTUAL  es: " << pintaNombreParametro(i_param_act)<<  endl ;

   //cout << "Indice del grado de libertad actual ahora es: " << i_param_act << endl ;
}

// -----------------------------------------------------------------------------
// acelerar las animaciones e incrementa el delta usado al increm./decrem. un parámetro
// (incrementa 'delta_valores_na')

void ObjJerarquico::acelerar()
{
   using namespace std ;
   delta_valores_na += 0.2 ;
   cout << "Acelerado, delta == " << delta_valores_na << endl ;
}

// -----------------------------------------------------------------------------
// decelera las animaciones y decrementa el delta usado al increm./decrem. un parámetro
// (decrementa 'delta_valores_na')

void ObjJerarquico::decelerar()
{
   using namespace std ;
   delta_valores_na = std::max( delta_valores_na-0.2, 0.2 ) ;
   cout << "Decelerado, delta == " << delta_valores_na << endl ;
}

// -----------------------------------------------------------------------------

// método que sirve para registrar el instante actual como instante de
// inicio de las animaciones.  Se debe llamar inmediatamente después de
// que el usuario active las animaciones con la tecla correspondiente.
// Pone 't_anim' a cero.
// (no usa ninguna orden de OpenGL)

void ObjJerarquico::inicioAnimaciones( )
{
   using namespace std ;
   using namespace std::chrono ;
   modo_animacion = true;
   cout << "Se inicia animacion JERARQUICO" << endl;
   ultima_actu = steady_clock::now() ;
}

void ObjJerarquico::pararAnimaciones()
{
   modo_animacion = false;
}

// -----------------------------------------------------------------------------

// función para actualizar el estado de los parámetros al instante de
// tiempo actual. Esta función debe llamarse cada cierto tiempo para ir
// actualizando el estado del objeto durante los intervalos de tiempo en
// los que las animaciones están activadas.
// (solo se debe invocar con las animaciones activadas)
// (no usa ninguna orden de OpenGL)

void ObjJerarquico::actualizarEstado()
{
   if(modo_animacion){
      using namespace std ;
      using namespace std::chrono ;
      assert( objparam != nullptr );

      // calcular el tiempo transcurrido desde la ultima actualización o
      // desde que se invocó a 'inicio_animaciones' (delta_t_s)

      const Instante   ahora      = steady_clock::now() ;
      const Duracion_s duracion_s = ahora - ultima_actu ;
      const float      delta_t_s  = duracion_s.count();

      //cout << "    Delta_t_s == " << delta_t_s << endl ;

      // actualizar instante de la última actualización de estado
      ultima_actu = ahora ;

      // incrementar los valores lineales, y en el objparam, actualizar los valores efectivos

      for( unsigned i = 1 ; i < 7 ; i++ )
      {
         if(i==1 || i==2 || i==5 || i==7){
         valores_na[i] += delta_t_s*delta_valores[i] ;
         objparam->actualizarValorEfe( i, valores_na[i] );
      }
      }
   }
}
