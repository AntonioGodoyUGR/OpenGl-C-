// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: GrafoParamatat.h
// -- declaraciones de clase para el objeto jerárquico de la práctica 3
//
// #############################################################################

#ifndef GRAFOPARAM_H_INCLUDED
#define GRAFOPARAM_H_INCLUDED

#include "malla.h" // añadir .h de cualquier objetos malla indexada usados....

constexpr int num_parametros = 8 ; // número de parámetros o grados de libertad
                                   // de este modelo

class GrafoParam
{
   public:

   // crea mallas indexadas (nodos terminales del grafo)
   GrafoParam();

   // función principal de visualización
   void draw( bool ajedre );

   // actualizar valor efectivo de un parámetro (a partir de su valor no acotado)
   void actualizarValorEfe( const unsigned iparam, const float valor_na );

   // devuelve el número de parámetros
   unsigned numParametros() { return num_parametros ; }

   private:

   // métodos de dibujo de subgrafos
   void PIE(double gpie, double gantebrazo, double gbrazo, double altura_pie, double altura_antebrazo, double altura_brazo, bool ajedre);


   // objetos tipo malla indexada (nodos terminales)

   ObjPLY * pie = nullptr;
   ObjPLY * antebrazo = nullptr;
   ObjPLY * brazo = nullptr;
   ObjPLY * cuerpo= nullptr;
   ObjPLY * cabeza = nullptr;
   ObjPLY * canon = nullptr;
   ObjPLY * minicanon = nullptr;

   // parámetros de la llamada actual (o última) a 'draw'
    // modo de envío (true -> diferido, false -> inmediato)


   // valores efectivos de los parámetros (angulos, distancias, factores de
   // escala, etc.....) calculados a partir de los valores no acotados
	float angulopie, angulobrazo, anguloantebrazo, desplazamiento_cabeza, desplazamiento_canon, desplazamiento_minicanon, desplazamiento;


} ;

#endif
