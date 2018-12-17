//Alumno: Antonio Godoy González

#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "jerarquico.h"

class Escena
{

   private:

   Ejes ejes;

   // variables que definen la posicion de la camara en coordenadas polares
   GLfloat Observer_distance;
   GLfloat Observer_angle_x;
   GLfloat Observer_angle_y;

   // variables que controlan la ventana y la transformacion de perspectiva
   GLfloat Width, Height, Front_plane, Back_plane;

   void clear_window();
	void dibujar_objeto_actual();

   // Transformación de cámara
	void change_projection( const float ratio_xy );
	void change_observer();

   int objeto_actual = 0 , // objeto actual (el que se visualiza)
       num_objetos   = 0 ; // número de objetos (actualizado al crear los objetos en el constructor)
   int modo=0;
   int modo_dibujado=0;
   // Objetos de la escena
   Cubo * cubo = nullptr ; // es importante inicializarlo a 'nullptr'
   Tetraedro * tetraedro = nullptr;
   ObjPLY * objply = nullptr; 
   ObjRevolucion * objrev =nullptr;
   Cilindro* objcil = nullptr;
   Cono * objcono = nullptr;
   Esfera * objesf = nullptr;
   ObjJerarquico * objjer = nullptr;
   luz * miluz = nullptr;
   luz * miluz2 = nullptr;
   Cuadro * cuadro = nullptr;
   
   
   bool animacion = false;
   bool animar_luz= false;
   bool ajedrez=false;
   bool luces= false;
   bool luces2=false;
   
   // completar: añadir punteros a tetraedro u otros (práctica 1),
   //            y a un objeto PLY y de revolución (práctica 2),
   //           y a un objeto jerarquico (práctica 3).
   // ......
	void conmutarAnimaciones();
	void animar();
   public:

   Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
	void dibujar() ;
	
	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );
	
	void mgeDesocupado();
	
};
#endif
