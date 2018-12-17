// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: jerarquico.h
// -- declaraciones de clase para el objeto jerárquico de la práctica 3
//
// #############################################################################

#ifndef JERARQUICO_H_INCLUDED
#define JERARQUICO_H_INCLUDED

#include <chrono>
#include "malla.h"
#include "grafoparam.h"

// tipo para registrar instantes de tiempo
typedef std::chrono::time_point<std::chrono::steady_clock> Instante ;

// tipo para duraciones en segundos (como números 'float', con parte fraccionaria)
typedef std::chrono::duration<float,std::ratio<1,1>> Duracion_s ;


class ObjJerarquico
{
   public:
      // inicialización: crear mallas indexadas, inicialización de parámetros
      ObjJerarquico();

      // visualizar el objeto, usando los valores actuales de los parámetros
      void draw(bool ajedre  );

      // incrementa el valor del parámetro o grado de libertad actual
      void incrementaParamAct();

      // decrementa el valor del parámetro o grado de libertad actual
      void decrementaParamAct() ;

      // activar el siguiente parámetro o grado de libertad actual
      void siguienteParametro() ;

      // acelerar las animaciones e incrementar el delta usado al
      // increm./decrem. un parámetro (incrementa 'delta_valores_na')
      void acelerar();

      // decelera las animaciones y decrementa el delta usado al
      // increm./decrem. un parámetro (decrementa 'delta_valores_na')
      void decelerar();

      // método que sirve para registrar el instante actual como instante de
      // inicio de las animaciones.  Se debe llamar inmediatamente después de
      // que el usuario active las animaciones con la tecla correspondiente
      // (no usa ninguna orden de OpenGL)
      void inicioAnimaciones( );

      // función para actualizar el estado de los parámetros al instante de
      // tiempo actual. Esta función debe llamarse cada cierto tiempo para ir
      // actualizando el estado del objeto durante los intervalos de tiempo en
      // los que las animaciones están activadas.
      // (solo se debe invocar con las animaciones activadas)
      // (no usa ninguna orden de OpenGL)
      void actualizarEstado();

   private:
      // puntero al objeto con el grafo de escena
      GrafoParam * objparam = nullptr ;

      // instante de ultima actualización de los parámetros, o bien de
      // la última llamada a 'inicio_animaciones'
      Instante ultima_actu  ;

      // vector de valores lineales de los parámetros
      std::vector<float> valores_na ;

      // índice del parámetro o grado de libertad actual
      unsigned i_param_act = 0 ;

      // delta de los valores no acotados para animaciones e incremento/decremento
      float delta_valores_na = 0.2 ;

} ;

#endif
