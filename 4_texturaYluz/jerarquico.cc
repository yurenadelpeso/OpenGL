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
// constructor: crea objparam y fija el valor inicial de los valores
// de los parámetros (lineales y efectivos)

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

void ObjJerarquico::draw( const ModoVis modo_vis, const bool usar_diferido )
{
   assert( objparam != nullptr );
   objparam->draw( modo_vis, usar_diferido );
}
float min(float a,float b){
   if(a<=b) return a;
   else return b;
}
float max(float a,float b){
   if(a>=b) return a;
   else return b;
}


// -----------------------------------------------------------------------------
// incrementa el parámetro actual


void ObjJerarquico::incrementaParamAct()
{
   using namespace std ;
   assert( objparam != nullptr );
   assert( i_param_act < objparam->numParametros() );

   valores_na[i_param_act] += delta_valores_na/20.0 ;
   objparam->actualizarValorEfe( i_param_act, valores_na[i_param_act] );
}

// -----------------------------------------------------------------------------
// decrementa el parámetro actual

void ObjJerarquico::decrementaParamAct()
{
   using namespace std ;
   assert( objparam != nullptr );
   assert( i_param_act < objparam->numParametros() );

   valores_na[i_param_act] -= delta_valores_na/20.0 ;
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
   cout << "Indice del grado de libertad actual ahora es: " << i_param_act << endl ;
}

// -----------------------------------------------------------------------------
// hacer que el parámetro actual sea el anterior

void ObjJerarquico::anteriorParametro()
{
   using namespace std ;
   assert( objparam != nullptr );
   assert( i_param_act < objparam->numParametros() );

   i_param_act = (i_param_act-1) % objparam->numParametros();
   cout << "Indice del grado de libertad actual ahora es: " << i_param_act << endl ;
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
   using namespace std ;
   using namespace std::chrono ;
   assert( objparam != nullptr );

   //cout << "Entra: ObjJerarquico::actualizarEstado" << endl ;

   // calcular el tiempo transcurrido desde la ultima actualización o
   // desde que se invocó a 'inicio_animaciones' (delta_t_s)

   const Instante   ahora      = steady_clock::now() ;
   const Duracion_s duracion_s = ahora - ultima_actu ;
   const float      delta_t_s  = duracion_s.count();

   //cout << "    Delta_t_s == " << delta_t_s << endl ;

   // actualizar instante de la última actualización de estado
   ultima_actu = ahora ;

   // incrementar los valores lineales, y en el objparam, actualizar los valores efectivos

   for( unsigned i = 13 ; i < num_parametros ; i++ )
   {
      valores_na[i] += delta_t_s*delta_valores_na ;
      objparam->actualizarValorEfe( i, valores_na[i] );
   }
}
