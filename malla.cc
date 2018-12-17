//Alumno: Antonio Godoy González
#include "aux.h"
#include "ply_reader.h"
#include "malla.h"


// *****************************************************************************
//
// Clase ObjMallaIndexada
//
// *****************************************************************************

// Visualización en modo inmediato con 'glDrawElements'

double pi=3.14;

void ObjMallaIndexada::draw_ModoInmediato()
{
  // visualizar la malla usando glDrawElements,
  // completar (práctica 1)
  // ...
  	if(!texVertices.empty()){
  		cargarTexturas();
  		dibujarTexturas();
  	}else{
  		
 		if(glIsEnabled(GL_LIGHTING)==GL_TRUE){
			activarMateriales();
			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(GL_FLOAT,0, normales_vertices.data() );
		}
		
		glEnableClientState( GL_COLOR_ARRAY );
		glEnableClientState( GL_VERTEX_ARRAY );
		glVertexPointer( 3, GL_FLOAT, 0, vertices.data() );
		glColorPointer(3, GL_FLOAT, 0, color_principal.data());
		if(ajedrez==false){
			glDrawElements( GL_TRIANGLES, triangulos.size()*3, GL_UNSIGNED_INT, triangulos.data() );
		}else{
			glDrawElements( GL_TRIANGLES, triangulos_pares.size()*3, GL_UNSIGNED_INT, triangulos_pares.data() );
			glColorPointer(3, GL_FLOAT, 0, color_secundario.data());
			glDrawElements( GL_TRIANGLES, triangulos_impares.size()*3, GL_UNSIGNED_INT, triangulos_impares.data() );
		}
		glDisableClientState( GL_COLOR_ARRAY );
		glDisableClientState( GL_VERTEX_ARRAY );
		
	}
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

GLuint ObjMallaIndexada::CrearVBO( GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram ){
	GLuint id_vbo ;
	// resultado: identificador de VBO
	glGenBuffers( 1, & id_vbo );
	// crear nuevo VBO, obtener identificador (nunca 0)
	glBindBuffer( tipo_vbo, id_vbo ); // activar el VBO usando su identificador

	// esta instrucción hace la transferencia de datos desde RAM hacia GPU
	glBufferData( tipo_vbo, tamanio_bytes, puntero_ram, GL_STATIC_DRAW );
	glBindBuffer( tipo_vbo, 0 );
	return id_vbo ;
}



void ObjMallaIndexada::draw_ModoDiferido(){

  
   	activarMateriales();
	
	if( id_vbo_ver == 0	){
		id_vbo_ver=CrearVBO( GL_ARRAY_BUFFER,3*vertices.size()*sizeof(float),vertices.data());
	}
	if( id_vbo_tri == 0	){
		id_vbo_tri=CrearVBO( GL_ELEMENT_ARRAY_BUFFER,3*triangulos.size()*sizeof(unsigned int),triangulos.data());
	}
	if( id_vbo_tri_par == 0	){
		id_vbo_tri_par=CrearVBO( GL_ELEMENT_ARRAY_BUFFER,3*triangulos_pares.size()*sizeof(unsigned int),triangulos_pares.data());
	}
	if( id_vbo_tri_impar == 0	){
		id_vbo_tri_impar=CrearVBO( GL_ELEMENT_ARRAY_BUFFER,3*triangulos_impares.size()*sizeof(unsigned int),triangulos_impares.data());
	}

	glBindBuffer( GL_ARRAY_BUFFER, id_vbo_ver ); // activar VBO de vértices
	glVertexPointer( 3, GL_FLOAT, 0, 0 );
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT,0, normales_vertices.data() );

	glBindBuffer( GL_ARRAY_BUFFER, 0 );

	glEnableClientState( GL_VERTEX_ARRAY );
	
	
	glEnableClientState( GL_COLOR_ARRAY );
	glColorPointer(3, GL_FLOAT, 0, color_principal.data());
	if(ajedrez==false){
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri );
		glDrawElements( GL_TRIANGLES, triangulos.size()*3, GL_UNSIGNED_INT, 0 );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
	}else{
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri_par );
		glDrawElements( GL_TRIANGLES, triangulos_pares.size()*3, GL_UNSIGNED_INT, 0);
		
		
		glColorPointer(3, GL_FLOAT, 0, color_secundario.data());
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri_impar );
		glDrawElements( GL_TRIANGLES, triangulos_impares.size()*3, GL_UNSIGNED_INT, 0);
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
	}

	glDisableClientState( GL_COLOR_ARRAY );
	
	glDisableClientState( GL_VERTEX_ARRAY );

}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void ObjMallaIndexada::draw_ajedrez(){
	
	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_COLOR_ARRAY );
	glVertexPointer( 3, GL_FLOAT, 0, vertices.data() ) ;
	
	glColorPointer(3, GL_FLOAT, 0, color_principal.data());
	glDrawElements( GL_TRIANGLES, 3*triangulos_pares.size(), GL_UNSIGNED_INT, triangulos_pares.data() ) ;
	glColorPointer(3, GL_FLOAT, 0, color_secundario.data());
	glDrawElements( GL_TRIANGLES, 3*triangulos_impares.size(), GL_UNSIGNED_INT, triangulos_impares.data() ) ;
	glDisableClientState( GL_COLOR_ARRAY );
	glDisableClientState( GL_VERTEX_ARRAY );


}

void ObjMallaIndexada::dibujarTexturas(){
   
   glEnable(GL_TEXTURE_2D);
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState (GL_TEXTURE_COORD_ARRAY_EXT);

   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, textura[0]);

   glVertexPointer(3, GL_FLOAT, 0, vertices.data());
   glTexCoordPointer(2, GL_FLOAT, 0, texVertices.data());


   glDrawElements( GL_TRIANGLES, triangulos.size()*3, GL_UNSIGNED_INT, triangulos.data());
   
   

   glDisableClientState(GL_VERTEX_ARRAY);
   glBindTexture(GL_TEXTURE_2D, 0);
   glDisable(GL_TEXTURE_2D);
	
}

void ObjMallaIndexada::draw(int modo, bool ajedre)
{
 
 	ajedrez=ajedre;
   switch(modo){
	case 0:
   		draw_ModoInmediato(); break;
	case 1:
		draw_ModoDiferido(); break;
   }
}
// -----------------------------------------------------------------------------
// Recalcula la tabla de normales de vértices (el contenido anterior se pierde)

void ObjMallaIndexada::calcular_normales_caras()
{	
	normales_caras.resize(triangulos.size());
	Tupla3f a,b,c;
	for(int in=0; in<triangulos.size(); in++){
		a=vertices[triangulos[in](1)]-vertices[triangulos[in](0)];
		b=vertices[triangulos[in](2)]-vertices[triangulos[in](0)];
		c=a.cross(b);
		float m=sqrt(c(0)*c(0)+c(1)*c(1)+c(2)*c(2));
		normales_caras[in] = Tupla3f(c(0)/m , c(1)/m, c(2)/m); 
		
		
	}
   
}

void ObjMallaIndexada::calcular_normales_vertices(){
	
	
	//initgauss();
	normales_vertices.resize(vertices.size());

	for(int i=0; i<vertices.size();i++){
		normales_vertices[i](0)=0.0;
		normales_vertices[i](1)=0.0;
		normales_vertices[i](2)=0.0;
	}
	for(int i=0;i<triangulos.size();i++){
		normales_vertices[triangulos[i](0)]=normales_vertices[triangulos[i](0)]+normales_caras[i];
		normales_vertices[triangulos[i](1)]=normales_vertices[triangulos[i](1)]+normales_caras[i];
		normales_vertices[triangulos[i](2)]=normales_vertices[triangulos[i](2)]+normales_caras[i];
	}
	
	float m;
	
	for(int i=0;i<vertices.size();i++){
		m = normales_vertices[i](0)*normales_vertices[i](0)+normales_vertices[i](1)*normales_vertices[i](1)+normales_vertices[i](2)*normales_vertices[i](2);
		normales_vertices[i] = { normales_vertices[i](0)/m, normales_vertices[i](1)/m, normales_vertices[i](2)/m };
	}


}

void ObjMallaIndexada::activarMateriales(){
	glEnable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mimaterial.difuso);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mimaterial.ambiente);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mimaterial.especular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mimaterial.brillo);
}


void luz::activar(GLenum luz_i, int a, int b, int c, float ang, float x, float y, float z){
	
	glEnable(GL_LIGHTING);
	
	glLightfv(luz_ind, GL_AMBIENT, luz_ambiente);
	glLightfv(luz_ind, GL_SPECULAR, luz_especular);
	glLightfv(luz_ind, GL_DIFFUSE, luz_difusa); 
	glLightfv(luz_ind, GL_POSITION, luz_punto);

}


luz::luz(GLenum p_luz_ind, Tupla4f luz_p, Tupla4f luz_a, Tupla4f luz_d, Tupla4f luz_e){

	luz_ind=p_luz_ind;
	luz_punto=luz_p;
	luz_ambiente=luz_a;
	luz_difusa=luz_d;
	luz_especular=luz_e;

}

void luz::apagar(){
	glDisable(GL_LIGHTING);
	glDisable(luz_ind);
}

Tupla4f luz::getPosicion(){
	return luz_punto;
	
}

void luz::animasao(){
	float alpha = 2*pi*1/1000;
	
	Tupla4f luz_punto_aux;
	
	luz_punto_aux(0) = luz_punto(0)*cos(alpha)+luz_punto(2)*sin(alpha);
	luz_punto_aux(2) = luz_punto(0)*-sin(alpha)+luz_punto(2)*cos(alpha);
	luz_punto_aux(1) = luz_punto(1);
	luz_punto_aux(3) = luz_punto(3);
	(double )luz_punto_aux(0);
	(double )luz_punto_aux(2);
	(double )luz_punto_aux(1);
	(double )luz_punto_aux(3);
	luz_punto= luz_punto_aux;
	
	
	activar(GL_LIGHT0, 0, 0, 0, 0, 0.6, 0, 0);
}

void ObjMallaIndexada::cargarTexturas(){

  std::vector<unsigned char> data;

   CImg<unsigned char> logo;
   logo.load("./perro.jpg");

   // empaquetamos bien los datos
   for (long y = 0; y < logo.height(); y ++)
      for (long x = 0; x < logo.width(); x ++)
      {
	 unsigned char *r = logo.data(x, y, 0, 0);
	 unsigned char *g = logo.data(x, y, 0, 1);
	 unsigned char *b = logo.data(x, y, 0, 2);
	 data.push_back(*r);
	 data.push_back(*g);
	 data.push_back(*b);
      }

   glGenTextures(1, &textura[0]);
   glBindTexture(GL_TEXTURE_2D, textura[0]);

   glActiveTexture(GL_TEXTURE0);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   // TRASFIERE LOS DATOS A GPU
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, logo.width(), logo.height(),
		0, GL_RGB, GL_UNSIGNED_BYTE, &data[0]);
}
	

// *****************************************************************************
//
// Clase Cubo (práctica 1)
//
// *****************************************************************************

Cubo::Cubo()
{

   // inicializar la tabla de vértices
   vertices =  {  { -0.5, -0.5, -0.5 }, // 0
                  { -0.5, -0.5, +0.5 }, // 1
                  { -0.5, +0.5, -0.5 }, // 2
                  { -0.5, +0.5, +0.5 }, // 3
                  { +0.5, -0.5, -0.5 }, // 4
                  { +0.5, -0.5, +0.5 }, // 5
                  { +0.5, +0.5, -0.5 }, // 6
                  { +0.5, +0.5, +0.5 }  // 7
               };

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

   triangulos = { { 0, 2, 4 }, { 4, 2, 6 },
                  { 1, 5, 3 }, { 3, 5, 7 },
                  { 1, 3, 0 }, { 0, 3, 2 },
                  { 5, 4, 7 }, { 7, 4, 6 },
                  { 1, 0, 5 }, { 5, 0, 4 },
                  { 3, 7, 2 }, { 2, 7, 6 }
                } ;
              
    //caras y colores
   for(int i=0; i<vertices.size();i++){
  	color_principal.push_back({0.3,0.3,0.3});	
  	color_secundario.push_back({0.0,0.0,0.0});
   }
   	for(int j=0; j<triangulos.size(); j++){
   		if(j%2==0){
   			triangulos_pares.push_back(triangulos[j]);
   		}else{
   			triangulos_impares.push_back(triangulos[j]);
   		}
   	}
   	
  //normales
  calcular_normales_caras();
  calcular_normales_vertices();
  
  
  //material
  mimaterial.difuso=Tupla4f(1.0,1.0,1.0,1.0);
  mimaterial.especular=Tupla4f(1.0,1.0,1.0,1.0);
  mimaterial.ambiente=Tupla4f(0.5,0.5,0.5,1.0);
  mimaterial.brillo=Tupla4f(0.5,0.5,0.5,1.0);
  
}

// *****************************************************************************
//
// Clase Tetraedro (práctica 1)
//
// *****************************************************************************

// completar .....
Tetraedro::Tetraedro()
{

   // inicializar la tabla de vértices
   vertices =  {  { -0.5, -0.5, -0.5 }, // 0
                  { +0.5, -0.5, -0.5 }, // 1
                  { 0, -0.5, +0.5 }, // 2
                  { 0, +0.5, 0 }      // 4
                 // { +0.5, -0.5, +0.5 }, // 5
                 // { +0.5, +0.5, -0.5 }, // 6
                 // { +0.5, +0.5, +0.5 }  // 7
               };

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

   triangulos = { { 0, 2, 3 }, { 2, 1, 3 },
                  { 0, 1, 2 }, { 1, 0, 3 },
                } ;
                
   	for(int i=0; i<vertices.size();i++){
   		color_principal.push_back({0.3,0.3,0.3});	
  		color_secundario.push_back({0.0,0.0,0.0});
   	}
   	for(int j=0; j<triangulos.size(); j++){
   		if(j%2==0){
   			triangulos_pares.push_back(triangulos[j]);
   		}else{
   			triangulos_impares.push_back(triangulos[j]);
   		}
   	}
   	
   	  //normales
  calcular_normales_caras();
  calcular_normales_vertices();
  
  
  //material
  mimaterial.difuso=Tupla4f(1.0,1.0,1.0,1.0);
  mimaterial.especular=Tupla4f(1.0,1.0,1.0,1.0);
  mimaterial.ambiente=Tupla4f(0.5,0.5,0.5,1.0);
  mimaterial.brillo=Tupla4f(0.5,0.5,0.5,1.0);
  
   	
   	
}

// *****************************************************************************
//
// Clase ObjPLY (práctica 2)
//
// *****************************************************************************

ObjPLY::ObjPLY( const std::string & nombre_archivo )
{
   // leer la lista de caras y vértices
   ply::read( nombre_archivo, vertices, triangulos );
   
   for(int i=0; i<vertices.size();i++){
  	color_principal.push_back({0.3,0.3,0.3});	
  	color_secundario.push_back({0.0,0.0,0.0});
   }
   for(int j=0; j<triangulos.size(); j++){
   	if(j%2==0){
   		triangulos_pares.push_back(triangulos[j]);
   	}else{
   		triangulos_impares.push_back(triangulos[j]);
   	}
   }
   
  //normales
  calcular_normales_caras();
  calcular_normales_vertices();
  
  
  //material
  mimaterial.difuso=Tupla4f(1.0,1.0,1.0,1.0);
  mimaterial.especular=Tupla4f(1.0,1.0,1.0,1.0);
  mimaterial.ambiente=Tupla4f(0.5,0.5,0.5,1.0);
  mimaterial.brillo=Tupla4f(0.5,0.5,0.5,1.0);
  
  
}


// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

void ObjRevolucion::crearMalla(const std::vector<Tupla3f> & perfil_original, int num_instancias_perfil){
		vertices.clear();
		triangulos.clear();
		int a, b;
		Tupla3f temporal;
		Tupla3f PoloS;
		Tupla3i triangulo1, triangulo2;
		double alpha;
		Tupla3f vertice_aux;
		//VERTICES
		for(int i=0;i<num_instancias_perfil; i++){
			for(int j=0;j<perfil_original.size();j++){
				vertice_aux=perfil_original[j];
				alpha=2*pi*i/num_instancias_perfil;
				temporal(0) = vertice_aux(0)*cos(alpha)+vertice_aux(2)*sin(alpha);
				temporal(1) = vertice_aux(1);
				temporal(2) =-sin(alpha)*vertice_aux(0)+vertice_aux(2)*cos(alpha);
				vertices.push_back(temporal);
				
			}
			 
		}
		/*
			revolucion en torno al eje x
			temporal(0) = vertice_aux(0);
			temporal(1) = vertice_aux(1)*cos(alpha)-vertice_aux(2)*sin(alpha);
			temporal(2) = vertice_aux(1)*sin(alpha)+vertice_aux(2)*cos(alpha);
			revolucion en torno al eje z
			temporal(0) = vertice_aux(0)*cos(alpha)-vertice_aux(2)*sin(alpha);
			temporal(1) = vertice_aux(0)*sin(alpha)-vertice_aux(2)*cos(alpha);
			temporal(2) = vertice_aux(2);
		*/
		//CARAS
		for(int i=0;i<num_instancias_perfil;i++){
			for(int j=0;j<perfil_original.size()-1;j++){
				a=perfil_original.size()*i+j;
				b=perfil_original.size()*((i+1)%num_instancias_perfil)+j;
				triangulo1 = {a,b,b+1};	
				triangulo2 = {a,b+1,a+1};		
				triangulos.push_back(triangulo1);
				triangulos.push_back(triangulo2);
			}
		}
		
		//TAPAS VERTICES
			PoloS= Tupla3f(0.0,perfil_original[0](1),0.0);
			vertices.push_back(PoloS);  //polo sur
			if(perfil_original[perfil_original.size()-1](1)>=1.0){
				PoloS= Tupla3f(0.0,perfil_original[perfil_original.size()-1](1),0.0);
			}else{
				PoloS= Tupla3f(0.0,1.0,0.0);
			}
			vertices.push_back(PoloS);  //polo norte
			
		//TAPAS TRIANGULOS
		for(int i=0;i<num_instancias_perfil;i++){
			//triangulo1= Tupla3i(vertices.size()-2,i*perfil_original.size(),((i+1)%num_instancias_perfil)*perfil_original.size());
			triangulo1= Tupla3i(((i+1)%num_instancias_perfil)*perfil_original.size(),i*perfil_original.size(),vertices.size()-2);
			triangulos.push_back(triangulo1);
			
		}
		
		for(int i=0;i<num_instancias_perfil;i++){
			triangulo2= Tupla3i(vertices.size()-1,((i+1)*(perfil_original.size())-1),(((i+1)%num_instancias_perfil)+1)*(perfil_original.size())-1);
			triangulos.push_back(triangulo2);
		}
}  


ObjRevolucion::ObjRevolucion( const std::string & nombre_ply_perfil )
{
	std::vector<Tupla3f> aux;
	ply::read_vertices(nombre_ply_perfil, aux);
	ObjRevolucion::crearMalla( aux , 10 );
   	for(int i=0; i<vertices.size();i++){
   		color_principal.push_back({0.3,0.3,0.3});	
  		color_secundario.push_back({0.0,0.0,0.0});
   	}
   	for(int j=0; j<triangulos.size(); j++){
   		if(j%2==0){
   			triangulos_pares.push_back(triangulos[j]);
   		}else{
   			triangulos_impares.push_back(triangulos[j]);
   		}
   	}

  //normales
  calcular_normales_caras();
  calcular_normales_vertices();
  
  
  //material
  mimaterial.difuso=Tupla4f(1.0,1.0,1.0,1.0);
  mimaterial.especular=Tupla4f(1.0,1.0,1.0,1.0);
  mimaterial.ambiente=Tupla4f(0.5,0.5,0.5,1.0);
  mimaterial.brillo=Tupla4f(0.5,0.5,0.5,1.0);
  




}

Cilindro::Cilindro( const int num_instancias_perfil, int num_vertices )
{
	std::vector<Tupla3f> aux;
	/*Tupla3f v1,v2;
	v1 ={1.0,1.0,0.0};
	v2 ={1.0,-1.0,0.0};
	*/
	Tupla3f v={1.0,-1.0,0.0};
	aux.push_back(v);
	double altura= 2.0/num_vertices;
	for(int i=1;i<num_vertices;i++){
		v(2)=0.0;
		v(0)=aux[i-1](0);
		v(1)=aux[i-1](1)+altura;
		
		aux.push_back(v);
	}
	//aux.push_back(v2);
	//aux.push_back(v1);
	this->crearMalla( aux , num_instancias_perfil);
   	for(int i=0; i<=vertices.size();i++){
   		color_principal.push_back({0.3,0.3,0.3});	
  		color_secundario.push_back({0.0,0.0,0.0});
   	}
   	for(int j=0; j<triangulos.size(); j++){
   		if(j%2==0){
   			triangulos_pares.push_back(triangulos[j]);
   		}else{
   			triangulos_impares.push_back(triangulos[j]);
   		}
   	}
   	
    //normales
  calcular_normales_caras();
  calcular_normales_vertices();
  
  
  //material
  mimaterial.difuso=Tupla4f(1.0,1.0,1.0,1.0);
  mimaterial.especular=Tupla4f(1.0,1.0,1.0,1.0);
  mimaterial.ambiente=Tupla4f(0.5,0.5,0.5,1.0);
  mimaterial.brillo=Tupla4f(0.5,0.5,0.5,1.0);
  
  
  //cargar texVertices
  /*Tupla3f aux72;
  for(int i=0;i<num_instancias_perfil;i++){
  	for(int j=0;j<num_vertices-1;j++){
  		aux72(0)=(i*(1/num_instancias_perfil));
  		aux72(1)=1-(j*(1/num_vertices));
  		aux72(2)=0.0;
  		
  		texVertices.push_back(aux72);
  		
  	}
  }
  
  //TAPAS
  
  texVertices.push_back(Tupla3f(0.5,1.0,0.0));
  texVertices.push_back(Tupla3f(0.5,0.0,0.0));*/
  
  //AÑADIR LAS TAPAS!!!!!!!!!!!
  
  
}

Cono::Cono(const int num_instancias_perfil, int num_vertices)
{
	std::vector<Tupla3f> aux;
	Tupla3f v;
	v={1.0,-1.0,0.0};
	aux.push_back(v);
	double altura=2.0/num_vertices;
	double anchura=1.0/num_vertices;
	for(int i=1;i<num_vertices;i++){
		v(2)=0.0;
		v(0)=aux[i-1](0)-anchura;
		v(1)=aux[i-1](1)+altura;
		
		aux.push_back(v);
	}
	crearMalla(aux, num_instancias_perfil);
   	for(int i=0; i<vertices.size();i++){
   		color_principal.push_back({0.3,0.3,0.3});	
  		color_secundario.push_back({0.0,0.0,0.0});
   	}
   	for(int j=0; j<triangulos.size(); j++){
   		if(j%2==0){
   			triangulos_pares.push_back(triangulos[j]);
   		}else{
   			triangulos_impares.push_back(triangulos[j]);
   		}
   	}
  
  //normales
  calcular_normales_caras();
  calcular_normales_vertices();
  
  
  //material
  mimaterial.difuso=Tupla4f(1.0,1.0,1.0,1.0);
  mimaterial.especular=Tupla4f(1.0,1.0,1.0,1.0);
  mimaterial.ambiente=Tupla4f(0.5,0.5,0.5,1.0);
  mimaterial.brillo=Tupla4f(0.5,0.5,0.5,1.0);
    

}

Esfera::Esfera(const int num_vert_perfil, const int num_instancias_perfil)
{
	std::vector<Tupla3f> aux;
	double alpha;
	Tupla3f v;
	
	for(int i=1;i<num_vert_perfil;i++){
		alpha=-(pi/2) + (i*pi/(num_vert_perfil+1));
		v(2)=0.0;
		v(0)=1.0*cos(alpha);
		v(1)=1.0*sin(alpha);
		
		aux.push_back(v);
	}
	crearMalla( aux , num_instancias_perfil);
   	for(int i=0; i<vertices.size();i++){
   		color_principal.push_back({0.3,0.3,0.3});	
  		color_secundario.push_back({0.0,0.0,0.0});
   	}
   	for(int j=0; j<triangulos.size(); j++){
   		if(j%2==0){
   			triangulos_pares.push_back(triangulos[j]);
   		}else{
   			triangulos_impares.push_back(triangulos[j]);
   		}
   	}
	calcular_normales_caras();
	calcular_normales_vertices();

	  mimaterial.difuso=Tupla4f(1.0,1.0,1.0,1.0);
	  mimaterial.especular=Tupla4f(1.0,1.0,1.0,1.0);
  	  mimaterial.ambiente=Tupla4f(0.5,0.5,0.5,1.0);
  	  mimaterial.brillo=Tupla4f(0.5,0.5,0.5,1.0);
  
 
  }
  
  




Cuadro::Cuadro()
{
	vertices= {{-1,-1,0},{1,-1,0},{1,1,0},{-1,1,0}};
	
	triangulos = {{0,2,3},{0,1,2}};
	
	texVertices = {{0.0,1.0},{1.0,1.0},{1.0,0.0},{0.0,0.0}};


}




