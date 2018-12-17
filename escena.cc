
// Alumno: Antonio Godoy Gonzalez

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
    Front_plane       = 0.1;
    Back_plane        = 2000.0;
    Observer_distance = 2.0;
    Observer_angle_x  = 0.0 ;
    Observer_angle_y  = 0.0 ;

    ejes.changeAxisSize( 5000 );
	
    // crear los objetos de las prácticas: Mallas o Jerárquicos....
    cubo = new Cubo();
    tetraedro = new Tetraedro();
    objply = new ObjPLY("beethoven");
    objrev = new ObjRevolucion("peon");
    objcil = new Cilindro(10,10);
    objcono = new Cono(10,10);
    objesf = new Esfera(10,10);
    objjer= new ObjJerarquico();
    
    
    miluz = new luz(GL_LIGHT0, Tupla4f(0.0,2.0,50.0,0.0),Tupla4f(1.0,1.0,1.0,1.0), Tupla4f(1.0,1.0,1.0,1.0),Tupla4f(1.0,1.0,1.0,1.0));
    miluz2 = new luz(GL_LIGHT1, Tupla4f(0.0,2.0,50.0,1.0),Tupla4f(1.0,1.0,1.0,1.0), Tupla4f(0.3,0.6,0.5,1.0),Tupla4f(1.0,0.5,1.0,1.0));   
    
   cuadro = new Cuadro();
    
    // .......completar: ...
    // .....
	
    num_objetos = 9 ; // se usa al pulsar la tecla 'O' (rotar objeto actual)
	
    luces = false;
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer

	/*Width  = UI_window_width/10;
	Height = UI_window_height/10;

   change_projection( float(UI_window_width)/float(UI_window_height) );
	glViewport( 0, 0, UI_window_width, UI_window_height );*/
	
	redimensionar(UI_window_width,UI_window_height);
}

// **************************************************************************
// Funcion que dibuja el objeto activo actual, usando su método 'draw'
// (llamada desde Escena::dibujar)
// ***************************************************************************

void Escena::dibujar_objeto_actual()
{
   using namespace std ;
   

   // (1) configurar OpenGL para el modo actual (puntos/lineas/sólido)
   //    llamar glPolygonMode, glColor... (y alguna cosas más), según dicho modo
   // .........completar (práctica 1)


   // (2) dibujar el objeto actual usando método 'draw' del objeto asociado al
   // valor entero en 'objeto_actual'
	
	glPointSize(3);
	glEnable(GL_CULL_FACE);
   switch (modo) {
	case 0:
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		break;
	case 1:
		glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 2:
		glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
		break;
	}
   

   if(luces){
   	glEnable(miluz->luz_ind);
   }else{
   	glDisable(miluz->luz_ind);
   }
   
   if(luces2){
   	glEnable(miluz2->luz_ind);
   }else{
   	glDisable(miluz2->luz_ind);
   }
   
   miluz->activar(GL_LIGHT0, 0, 0, 0, 0, 0, 0, 0);
   
   switch( objeto_actual )
   {
      case 0:	
		cubo->draw(modo_dibujado,ajedrez); break ;
      case 1:
		tetraedro->draw(modo_dibujado,ajedrez); break;
      case 2:
		objply->draw(modo_dibujado,ajedrez); break;
      case 3:
		objrev->draw(modo_dibujado,ajedrez); break;
      case 4:
		objcil->draw(modo_dibujado,ajedrez); break;
      case 5:
		objcono->draw(modo_dibujado,ajedrez); break;
      case 6:
		objesf->draw(modo_dibujado,ajedrez); break;
      case 7: 
      		glScalef(5.0f,5.0f,5.0f);
      		objjer->draw(ajedrez); break;
      case 8:
      		cuadro->draw(modo_dibujado, ajedrez); break;
      default:
         cout << "draw_object: el número de objeto actual (" << objeto_actual << ") es incorrecto." << endl ;
         break ;
   }
}

// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::mgeDesocupado(){
	using namespace std;
	
	objjer->actualizarEstado();
	
	miluz2->animasao();
	glutPostRedisplay();
	
	//cout<<"x : "<<miluz2->getPosicion()(0)<<endl;
	//cout<<"z : "<<miluz2->getPosicion()(2)<<endl;
}

void Escena::conmutarAnimaciones(){
	if(animacion==false){
		animacion=true;
		objjer->inicioAnimaciones();
	}else{
		animacion=false;
	}
	
	if(animacion==true){
		glutIdleFunc(funcion_desocupado);
	}else{
		glutIdleFunc(nullptr);
	}
}

void Escena::animar(){
	
	if(animar_luz==false){
		animar_luz=true;
		//miluz2->activar(GL_LIGHT1, 0, 0, 0, 0, 0.6, 0, 0);
	}else{
		animar_luz=false;
	}
	
	
	if(animar_luz==true){
		glutIdleFunc(funcion_desocupado);
	}else{
		glutIdleFunc(nullptr);
	}

}

void Escena::dibujar()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
   	ejes.draw();
	dibujar_objeto_actual();
	
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;
   cout << "Tecla pulsada: '" << tecla << "'" << endl;

   switch( toupper(tecla) )
   {
      case 'Q' :
         // salir
         return true ;
         break ;
      case 'O' :
         // activar siguiente objeto
         objeto_actual = (objeto_actual+1) % num_objetos ;
         cout << "objeto actual == " << objeto_actual << endl ;
         break ;
	  case 'P' :
		 cout << "cambio de modo a Puntos" << endl;
		 modo = 0;
		 break;
	  case 'L' :
		 cout << "cambio de modo a Lineas" << endl;
		 modo = 1;
		 break;
	  case 'F' :
		 cout << "cambio de modo a Relleno" << endl;
		 modo = 2;
		 break;
	  case 'C' :
		 cout << "cambio de modo a Ajedrez" << endl;
		 ajedrez = !ajedrez;
		 break;
	  case 'I' :
		 cout << "cambio de metodo de Dibujado a Inmediato" << endl;
		 modo_dibujado= 0;
		 break;
	  case 'D' :
		 cout << "cambio de metodo de Dibujado a Diferido" << endl;
		 modo_dibujado= 1;
		 break;
	  case 'A' :
	  	conmutarAnimaciones(); 
	  	break;
	  case '<' :
	  	objjer->decelerar();
	  	break;
	  case '>' :
	  	objjer->acelerar();
	  	break;
	  case 'X' :
	  	objjer->siguienteParametro();
	  	break;
	  case 'Z' :
	  	objjer->incrementaParamAct();
	  	break;
	  case '1' :
	  	luces = !luces;
	  	break;
	  case '2' :
	  	luces2 = !luces2;
	  	animar();
	  	break;
	  case '3' :
	  	miluz->apagar();
	  	break;
	  case '4' :
	  	miluz2->apagar();
	  	break;
	  case 'Y' :
	  	luces = !luces;
	  	break;
   }
   return false ;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         Observer_angle_y-- ;
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y++ ;
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x-- ;
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x++ ;
         break;
	   case GLUT_KEY_PAGE_UP:
         Observer_distance *=1.2 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.2 ;
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wy = 0.84*Front_plane, wx=ratio_xy*wy;
   glFrustum( -wx, wx, -wy, wy, Front_plane, Back_plane );
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth;
   Height = newHeight;
   change_projection( float(Height)/float(Width) );
   glViewport( 0, 0, Width, Height );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_y, 1.0 ,0.0, 0.0 );
   glRotatef( Observer_angle_x, 0.0, 1.0, 0.0 );
}
