// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: GrafoParam.h
// -- declaraciones de clase para el objeto jerárquico de la práctica 3
//
// #############################################################################

#ifndef GRAFOPARAM_H_INCLUDED
#define GRAFOPARAM_H_INCLUDED

#include "malla.h"

constexpr int num_parametros = 8 ; // número de parámetros o grados de libertad
//unsigned numObjeto;                           


class GrafoParam
{
   public:

   // crea mallas indexadas (nodos terminales del grafo)
   GrafoParam();

   // función principal de visualización
   void draw( const int p_modo_vis, const bool p_usar_diferido );

   // actualizar valor efectivo de un parámetro (a partir de su valor no acotado)
   void actualizarValorEfe( const unsigned iparam, const float valor_na );

   // devuelve el número de parámetros
   unsigned numParametros() { return num_parametros ; }
  


   private:
   void miDibujo(const int p_modo_vis, const bool p_usar_diferido);//araña
   void miDibujo1(const int p_modo_vis, const bool p_usar_diferido); //tanque
   void miDibujo2(const int p_modo_vis, const bool p_usar_diferido);

   void miDibujo3(const int p_modo_vis, const bool p_usar_diferido);//excavadora
   void miDibujo4(const int p_modo_vis, const bool p_usar_diferido);//excavadora

   void dibujoExamen(const int p_modo_vis, const bool p_usar_diferido);//tanqueta



/*
*
*para componer la tanqueta
*
*/
void ruedaTanqueta(const int p_modo_vis, const bool p_usar_diferido);

/*
*
*para componer la nuevaAraña
*
*/

   void  nuevaAranya(const int p_modo_vis, const bool p_usar_diferido);
   void  nuevoCuerpo(const int p_modo_vis, const bool p_usar_diferido);
   void  nuevaPata_0(const int p_modo_vis, const bool p_usar_diferido);
   void  nuevaPata_1(const int p_modo_vis, const bool p_usar_diferido);
   void  nuevaPata_2(const int p_modo_vis, const bool p_usar_diferido);
   void  nuevaPata_3(const int p_modo_vis, const bool p_usar_diferido);
   void  nuevaPataCompleta(const int p_modo_vis, const bool p_usar_diferido);





/*
*
*para componer el tanque
*
*/

   void palaGrande(const int p_modo_vis, const bool p_usar_diferido);

/*
*
*para componer el tanque
*
*/

   void rueda(const int p_modo_vis, const bool p_usar_diferido);
   void parRueda(const int p_modo_vis, const bool p_usar_diferido);
   void cuerpoBajo(const int p_modo_vis, const bool p_usar_diferido);
   void cuatroRuedas(const int p_modo_vis, const bool p_usar_diferido);
   void cuerpoAlto(const int p_modo_vis, const bool p_usar_diferido);
   void canyon(const int p_modo_vis, const bool p_usar_diferido);
   void tanque(const int p_modo_vis, const bool p_usar_diferido);
   void capsula(const int p_modo_vis, const bool p_usar_diferido);
   void canyonExtensible(const int modo_vis, const bool usar_diferido);
   void tapa(const int modo_vis, const bool usar_diferido);
   void pala(const int modo_vis, const bool usar_diferido);




/*
*
*para componer la araña
*
*/

   void  aranya(const int p_modo_vis, const bool p_usar_diferido);
   void  pata_0(const int p_modo_vis, const bool p_usar_diferido);
   void  pata_1(const int p_modo_vis, const bool p_usar_diferido);
   void  pata_2(const int p_modo_vis, const bool p_usar_diferido);
   void  pata_3(const int p_modo_vis, const bool p_usar_diferido);
   void  pata_completa(const int p_modo_vis, const bool p_usar_diferido);
   void  cuerpo(const int p_modo_vis, const bool p_usar_diferido);
   void  abdomen(const int p_modo_vis, const bool p_usar_diferido);
   void  cabeza(const int p_modo_vis, const bool p_usar_diferido);
   void  ojo(const int p_modo_vis, const bool p_usar_diferido);
   void  pinza(const int p_modo_vis, const bool p_usar_diferido);
   void  extremoPinza(const int p_modo_vis, const bool p_usar_diferido);
   void  abdomen1(const int p_modo_vis, const bool p_usar_diferido);


   /*
   *
   * Tanqueta del examen
   *
   *
   */

   void  tanqueta(const int p_modo_vis, const bool p_usar_diferido);
   void  soporte(const int p_modo_vis, const bool p_usar_diferido);
   void  planchas(const int p_modo_vis, const bool p_usar_diferido);












   // objetos tipo malla indexada (nodos terminales)

   Cilindro *cilindro = nullptr;
   Cubo     *cubo     = nullptr;
   Esfera   *esfera   = nullptr;
   Cono     *cono     = nullptr;
   Cupula   *cupula   = nullptr;

  
   // parámetros de la llamada actual (o última) a 'draw'
   int modo_vis ;      // modo de visualización
   bool usar_diferido ; // modo de envío (true -> diferido, false -> inmediato)


   // valores efectivos de los parámetros (angulos, distancias, factores de
   // escala, etc.....) calculados a partir de los valores no acotados

   

   std::vector<float> movimientos;
   float rotarcilindro;
   float rotarcanyon;
   float canyonArriba;
   float abrirTapa;
         
   float extenderCanyon, rotarTapa,rotarExtremo,
   rotarRuedasA,avanzarTanque,subirCubo,
         patasImpares,  
         movimientoAbdomen,       
         ag_rotacion_2 ; 
   
 //PARAMETROS DE MOVIMIENTO DE LA TANQUETA
   float rotarRuedas, rotarAmbasPlanchas, deslizarPlancha;

} ;

#endif