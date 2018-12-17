// #############################################################################
//
// Informática Gráfica (Grado Informática)
// Alumno: Antonio Godoy González
// Archivo: ObjMallaIndexada.h
// -- declaraciones de clase ObjMallaIndexada (mallas indexadas) y derivados
//
// #############################################################################

#ifndef OBJETOS_H_INCLUDED
#define OBJETOS_H_INCLUDED

#include "aux.h"
#include "CImg.h"
using namespace cimg_library;
// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

struct material{
	Tupla4f difuso;
	Tupla4f especular;
	Tupla4f ambiente;
	Tupla4f brillo;
};

class ObjMallaIndexada
{
   public:

   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato();
   GLuint CrearVBO( GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram );
   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido();

   // función que redibuja el objeto
   // está función llama a 'draw_MI' (modo inmediato)
   // o bien a 'draw_MD' (modo diferido, VBOs)
   void draw(int modo,bool ajedre) ;
   void draw_ajedrez();
   void calcular_normales_caras();
   void calcular_normales_vertices();
   void activarMateriales();
   void cargarTexturas();
   void dibujarTexturas();
  
   
   protected:

   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)

   std::vector<Tupla3f> vertices ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> triangulos ; // una terna de 3 enteros por cada cara o triángulo
   std::vector<Tupla3f> color_principal;
   std::vector<Tupla3f> color_secundario;
   std::vector<Tupla3i> triangulos_impares;
   std::vector<Tupla3i> triangulos_pares;
   std::vector<Tupla3f> normales_vertices;
   std::vector<Tupla3f> normales_caras;
   GLuint id_vbo_tri=0;
   GLuint id_vbo_ver=0;
   GLuint id_vbo_tri_par=0;
   GLuint id_vbo_tri_impar=0;
   //GLfloat texVertices[1000000];
   std::vector<Tupla2f> texVertices;
   
   material mimaterial;

   GLuint textura[1];
   
   bool ajedrez= false;
   
   // completar: tabla de colores, tabla de normales de vértices
} ;

// *****************************************************************************
//
// clases derivadas de ObjMallaIndexada (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cubo con centro en el origen y lado unidad
// (tiene 9 vertices y 6 caras)

class Cubo : public ObjMallaIndexada
{
   public:
   Cubo() ;

} ;

class Tetraedro : public ObjMallaIndexada
{
   public:
   Tetraedro() ;

} ;


// *****************************************************************************
// objeto leído de un archivo PLY

class ObjPLY : public ObjMallaIndexada
{
   public:
      ObjPLY( const std::string & nombre_archivo );

} ;

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

class ObjRevolucion : public ObjMallaIndexada
{
   public:
      ObjRevolucion( const std::string & nombre_ply_perfil );
      ObjRevolucion(){};
   protected: 
      void crearMalla(const std::vector<Tupla3f> & perfil_original,int num_instancias_perfil);
      
} ;

class Cilindro : public ObjRevolucion
{
	public:
		Cilindro( const int num_instancias_perfil, int num_vertices);

};

class Esfera : public ObjRevolucion
{
	public:
		Esfera(const int num_vert_perfil, const int num_instancias_perfil);

};

class Cono : public ObjRevolucion
{
	public:
		Cono( const int num_instancias_perfil, int num_vertices);
  	
};


class luz
{
	public:
		luz(GLenum p_luz_ind, Tupla4f luz_p, Tupla4f luz_a, Tupla4f luz_d, Tupla4f luz_e);
		void activar(GLenum luz_i, int a, int b, int c, float ang, float x, float y, float z);
		void apagar();
		Tupla4f getPosicion();
		void animasao();
		GLenum luz_ind;
	protected:
		
		Tupla4f luz_punto;
		Tupla4f luz_ambiente;
		Tupla4f luz_difusa;
		Tupla4f luz_especular;		
};

class Cuadro : public ObjMallaIndexada
{
	public:
		Cuadro();	
	        
	        
	protected:
		
		

};


#endif
