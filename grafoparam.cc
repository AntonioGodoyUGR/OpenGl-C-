// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: GrafoParam.cc
// -- implementación del objeto jerárquico de la práctica 3
//
// #############################################################################


#include "grafoparam.h"

// -----------------------------------------------------------------------------
// constructor: crea mallas indexadas en los nodos terminales del grafo

GrafoParam::GrafoParam()
{
   pie = new ObjPLY("pie");
   antebrazo = new ObjPLY("antebrazo");
   brazo = new ObjPLY("brazo");
   cuerpo = new ObjPLY("cuerpo");
   cabeza = new ObjPLY("cabeza");
   canon = new ObjPLY("canon");
   minicanon=new ObjPLY("minicanon");
}
// -----------------------------------------------------------------------------
// actualizar valor efectivo de un parámetro (a partir de su valor no acotado)

void GrafoParam::actualizarValorEfe( const unsigned iparam, const float valor_na )
{
   assert( iparam < num_parametros );

   using namespace std ;
   //cout << "GrafoParam::actualizarValorEfe( " << iparam << ", " << valor_na << " )" << endl ;

   constexpr float vp = 1.0 ;

   switch( iparam )
   {
      case 0:
         // altura 1: oscila entre 0.7 y 1.3, a 0.5 oscilaciones por segundo
         // inicialmente es 1.0 (media de los valores extremos)
         desplazamiento= 0.0 + 0.5*sin( 0.5*(2.0*M_PI*valor_na) );
         break ;
      case 1:
         // altura 2: oscila entre 1.1 y 1.9, a 0.8 oscilaciones por segundo
         //altura_2 = 1.5 + 0.4*sin( 0.8*(2.0*M_PI*valor_na) );
         desplazamiento_cabeza=0.0 + 0.015*sin( 0.5*(2.0*M_PI*valor_na) );
         break ;
      case 2:
         // angulo en grados de rotacion 1 (cubo rojoaa)
         // crece linealmente a 150 grados por segundo, inicialmente es 20 grados
         angulopie = 0.0 + 30*sin( 1.5*(2.0*M_PI*valor_na) );
         break ;
      case 3:
         // ángulo en grados de rotacion 2 (cubo azul)
         // oscila entre -45 y 30 grados, a 1.5 oscilaciones por segundo
         // (inicialmente es -7.5 grados)
         anguloantebrazo= 0.0 + 30*sin( 1.5*(2.0*M_PI*valor_na) );
         break ;
      case 4:
         // ángulo en grados de rotacion 2 (cubo azul)
         // oscila entre -45 y 30 grados, a 1.5 oscilaciones por segundo
         // (inicialmente es -7.5 grados)
         angulobrazo= 10.0 + 10*sin( 1.5*(2.0*M_PI*valor_na) );
         break ;
      case 5:
      	  desplazamiento_canon = 0.0 + 0.002*sin(1.5*(2.0*M_PI*valor_na));
      	  break;
      case 6:
      	  desplazamiento_minicanon = 0.0 + 0.001*sin(1.5*(2.0*M_PI*valor_na));  
   	  break;
   }
}

// -----------------------------------------------------------------------------
// visualización del objeto Jerárquico con OpenGL,
// mediante llamadas a los métodos 'draw' de los sub-objetos

void GrafoParam::draw(bool ajedre )
{
   // asegurarnos que está inicializado ok

   assert( pie   != nullptr );
   assert( antebrazo != nullptr );
   assert(brazo != nullptr);
   assert(cuerpo!=nullptr);
   assert(cabeza!=nullptr);
   assert(canon!=nullptr);
   assert(minicanon!=nullptr);
   // guardar parametros de visualización para esta llamada a 'draw'
   // (modo de visualización, modo de envío)


   // dibujar objetos
 
 				//////////////////////////////////ARREGLAR PLYS////////////////////////////7777
 				////////////////////////PREGUNTAR POR DISTINTAS VELOCIDADES////////////////////
 				
 	double altura_pie=0.09532;
 	double altura_antebrazo=0.34032;
 	double altura_brazo=0.13725;
	desplazamiento = 0.0;
   glPushMatrix();
   	glTranslatef(0.0,0.0,desplazamiento);
   	glPushMatrix();
   		glTranslatef(0.0,altura_pie+(altura_antebrazo/2),0.04);
   		glRotatef(270,1.0,0.0,0.0);
   		cuerpo->draw(0, ajedre);
   	glPopMatrix();
   	glPushMatrix();
   		glTranslatef(0.0,desplazamiento_cabeza,0.0);
	   	glPushMatrix();
	   		glTranslatef(0.0,altura_pie+(altura_antebrazo/2),-0.20);
	   		glRotatef(270,1.0,0.0,0.0);
	   		cabeza->draw(0, ajedre);
	   	glPopMatrix();
	   	////////////////////////MINICAÑONES///////////////////////
	   	glPushMatrix();
	   		glTranslatef(0.0,0.0,desplazamiento_minicanon);
		   	glPushMatrix();
		   		glTranslatef(0.045,altura_pie+(altura_antebrazo/2),-0.22);
		   		glRotatef(270,1.0,0.0,0.0);
		   		minicanon->draw(0, ajedre);
		   	glPopMatrix();
		   	glPushMatrix();
		   		glTranslatef(-0.045,altura_pie+(altura_antebrazo/2),-0.22);
		   		glRotatef(270,1.0,0.0,0.0);
		   		minicanon->draw(0, ajedre);
		   	glPopMatrix();
	   	glPopMatrix();
	   	////////////////////////CAÑONES////////////////////////
	   	glPushMatrix();
		   	glTranslatef(0.0,0.0,desplazamiento_canon);
		   	glPushMatrix();
		   		glTranslatef(0.03,altura_pie+(altura_antebrazo/2)-0.03,-0.22);
		   		glRotatef(270,1.0,0.0,0.0);
		   		canon->draw(0, ajedre);
		   	glPopMatrix();
		   	glPushMatrix();
		   		glTranslatef(-0.03,altura_pie+(altura_antebrazo/2)-0.03,-0.22);
		   		glRotatef(270,1.0,0.0,0.0);
		   		canon->draw(0, ajedre);
		   	glPopMatrix();
	   	glPopMatrix();
	 glPopMatrix();
   	///////////////////////PIES////////////////////////////
   	glPushMatrix();
   		//glRotatef(angulobrazo,1.0,0.0,0.0);
   		
   		glTranslatef(-0.05,0.0,0.07);
    		
    		PIE(angulopie,anguloantebrazo,angulobrazo,altura_pie,altura_antebrazo,altura_brazo, ajedre);
   	glPopMatrix();
   	glPushMatrix();
   		//glRotatef(angulobrazo,1.0,0.0,0.0);
   		glTranslatef(-0.05,0.0,-0.07);
    		
    		PIE(-angulopie,-anguloantebrazo,20.0-angulobrazo,altura_pie,altura_antebrazo,altura_brazo, ajedre);
   	glPopMatrix();
   	glPushMatrix();
   		
   		glTranslatef(0.05,0.0,-0.07);
    		
    		PIE(angulopie,anguloantebrazo,angulobrazo,altura_pie,altura_antebrazo,altura_brazo, ajedre);
   	glPopMatrix();
   	//glRotatef(angulobrazo,1.0,0.0,0.0);
    	glTranslatef(0.05,0.0,0.07);
    	
    	PIE(-angulopie,-anguloantebrazo,20.0-angulobrazo,altura_pie,altura_antebrazo,altura_brazo, ajedre);
   glPopMatrix();
}
// -----------------------------------------------------------------------------
// dibuja un sub-objeto parametrizado:
// es una columna (cilindro) de altura = 'altura', con un cubo encima,
// rotado entorno a Y un ángulo en grados = 'ag_rotacion'

void GrafoParam::PIE(double gpie,double gantebrazo,double gbrazo, double altura_pie,double altura_antebrazo, double altura_brazo, bool ajedre){
	
	glPushMatrix();
		glTranslatef(0.0, (0.20+(altura_brazo/2)), 0.0);
		glRotatef(gbrazo,1.0,0.0,0.0);
		glTranslatef(0.0, -(0.20+(altura_brazo/2)), 0.0);
		glPushMatrix();
			glTranslatef(0.0, 0.20, 0.0);
			glRotatef(270,1.0,0.0,0.0);
			brazo->draw(0, ajedre);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0,(altura_pie+(0.05152)/2),0.0);
			glRotatef(-gbrazo,1.0,0.0,0.0);
			glTranslatef(0.0,-(altura_pie+(0.05152)/2),0.0);
			glPushMatrix();
				glTranslatef(0.0,altura_pie,0.0);
				glRotatef(270,1.0,0.0,0.0);
				antebrazo->draw(0, ajedre);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0, (altura_pie/4)-0.01, 0.0);
				glRotatef(gbrazo, 1.0,0.0,0.0);
				glRotatef(270,1.0,0.0,0.0);
				pie->draw(0, ajedre);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	
 
}
