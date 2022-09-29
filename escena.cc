

#include "auxiliar.h" // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
   Front_plane = 50.0;
   Back_plane = 2000.0;
   Observer_distance = 4 * Front_plane;
   Observer_angle_x = 0.0;
   Observer_angle_y = 0.0;

   ejes.changeAxisSize(5000);

   // crear los objetos de la escena....
   // .......completar: ...
   // .....
   cubo = new Cubo(50);

   piramide = new PiramidePentagonal(50, 50);
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar(int UI_window_width, int UI_window_height)
{
   glClearColor(1.0, 1.0, 1.0, 1.0); // se indica cual sera el color para limpiar la ventana	(r,v,a,al)

   glEnable(GL_DEPTH_TEST); // se habilita el z-bufer

   Width = UI_window_width / 10;
   Height = UI_window_height / 10;

   change_projection(float(UI_window_width) / float(UI_window_height));
   glViewport(0, 0, UI_window_width, UI_window_height);
}

// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpiar la pantalla
   change_observer();
   ejes.draw();

   glEnable(GL_CULL_FACE);

   //  COMPLETAR
   //    Dibujar los diferentes elementos de la escena
   //  Habrá que tener en esta primera práctica una variable que indique qué objeto se ha de visualizar
   //  y hacer
   //  cubo->draw()
   //  o    piramide->draw()

   if(visual_obj[0]){

      glPointSize(5);
      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

      if(piramide_cubo){

         piramide->rellenar_color(Tupla3f(0, 1, 0));

         piramide->draw();

      }else{

         cubo->rellenar_color(Tupla3f(1, 0, 0));

         cubo->draw();
      }
      
   }

   if(visual_obj[1]){
      
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

      if(piramide_cubo){

         piramide->rellenar_color(Tupla3f(1, 0, 0));

         piramide->draw();

      }else{

         cubo->rellenar_color(Tupla3f(0, 1, 0));

         cubo->draw();
      }

   }

   if(visual_obj[2]){

      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      if(piramide_cubo){

         piramide->rellenar_color(Tupla3f(0, 0, 1));


         piramide->draw();
      }else{

         cubo->rellenar_color(Tupla3f(0, 0, 1));

         cubo->draw();
      }

   }
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada(unsigned char tecla, int x, int y)
{
   using namespace std;
   cout << "Tecla pulsada: '" << tecla << "'" << endl;
   bool salir = false;
   switch (toupper(tecla))
   {
   case 'Q':
      if (modoMenu != NADA){
         modoMenu = NADA;
         cout << "Salir del menu" << endl;
      }
      else
      {
         cout << "Salir del programa" << endl;
         salir = true;
      }
      break;
   case 'O':
      // ESTAMOS EN MODO SELECCION DE OBJETO

      if(modoMenu == NADA){

         // SI NO ESTAMOS EN NINGÚN MENÚ ENTRAMOS EN
         // MENÚ DE SELECCIÓN DE OBJETO.

         modoMenu = SELOBJETO;
         cout << "Menu de seleccion de objeto" << endl;

      }else{

         // EN CUALQUIER CASO QUE NO SEA ESE,
         // LA SELECCIÓN NO SERÁ VÁLIDA.

         cout << "Seleccion no valida" << endl;
      }

      break;
   case 'V':
      // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION

      if(modoMenu == NADA){

         // SI NO ESTAMOS EN NINGÚN MENÚ ENTRAMOS EN
         // MENÚ DE SELECCIÓN DE MODO DE VISUALIZACIÓN.

         modoMenu = SELVISUALIZACION;
         cout << "Menu de seleccion de modo de visualizacion" << endl;

      }else{

         // EN CUALQUIER CASO QUE NO SEA ESE,
         // LA SELECCIÓN NO SERÁ VÁLIDA.

         cout << "Seleccion no valida" << endl;
      }

      break;

      // COMPLETAR con los diferentes opciones de teclado
      // SE VISUALIZA CUBO
   case 'C':

      // SI ESTAMOS EN EL MENÚ DE SELECCIÓN DE OBJETO
      if(modoMenu = SELOBJETO){

         // VISUALIZAMOS CUBO

         piramide_cubo = false;

         cout << "Visualizando cubo" << endl;

      }else{

         // EN CUALQUIER CASO QUE NO SEA ESE,
         // LA SELECCIÓN NO SERÁ VÁLIDA.

         cout << "Seleccion no valida" << endl;

      }

      break;

      // SE VISUALIZA PIRAMIDE
   case 'P':

      if(modoMenu = SELOBJETO){

         // VISUALIZAMOS PIRAMIDE

         piramide_cubo = true;

         cout << "Visualizando piramide" << endl;
         
      }else{
            
         // EN CUALQUIER CASO QUE NO SEA ESE,
         // LA SELECCIÓN NO SERÁ VÁLIDA.

         cout << "Seleccion no valida" << endl;
   
      }

      break;

      // SE VISUALIZA EL OBJETO MODO PUNTOS
   case 'D':

      if(modoMenu == SELVISUALIZACION){

         visual_obj[0] = !visual_obj[0];

         if(visual_obj[0]){

            cout << "Activado modo puntos" << endl;

         }else{

            cout << "Desactivado modo puntos" << endl;
         }

         cout << visual_obj[0] << endl;

      }else{
            
         // EN CUALQUIER CASO QUE NO SEA ESE,
         // LA SELECCIÓN NO SERÁ VÁLIDA.

         cout << "Seleccion no valida" << endl;
   
      }

      break;

      // SE VISUALIZA EL OBJETO MODO LINEAS
   case 'L':

      if(modoMenu == SELVISUALIZACION){

         visual_obj[1] = !visual_obj[1];

         if(visual_obj[1]){

            cout << "Modo lineas activado" << endl;

         }else{

            cout << "Modo lineas desactivado" << endl;
            
         }
         
      }else{
            
         // EN CUALQUIER CASO QUE NO SEA ESE,
         // LA SELECCIÓN NO SERÁ VÁLIDA.

         cout << "Seleccion no valida" << endl;
   
      }

      break;

      // SE VISUALIZA EL OBJETO MODO SOLIDO
   case 'S':

      if(modoMenu == SELVISUALIZACION){

         visual_obj[2] = !visual_obj[2];

         if(visual_obj[2]){

            cout << "Modo solido activado" << endl;

         }else{

            cout << "Modo puntos desactivado" << endl;
         }
         
      }else{
            
         // EN CUALQUIER CASO QUE NO SEA ESE,
         // LA SELECCIÓN NO SERÁ VÁLIDA.

         cout << "Seleccion no valida" << endl;
   
      }

      break;
   }
   return salir;
}
//**************************************************************************

void Escena::teclaEspecial(int Tecla1, int x, int y)
{
   switch (Tecla1)
   {
   case GLUT_KEY_LEFT:
      Observer_angle_y--;
      break;
   case GLUT_KEY_RIGHT:
      Observer_angle_y++;
      break;
   case GLUT_KEY_UP:
      Observer_angle_x--;
      break;
   case GLUT_KEY_DOWN:
      Observer_angle_x++;
      break;
   case GLUT_KEY_PAGE_UP:
      Observer_distance *= 1.2;
      break;
   case GLUT_KEY_PAGE_DOWN:
      Observer_distance /= 1.2;
      break;
   }

   // std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection(const float ratio_xy)
{
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   const float wx = float(Height) * ratio_xy;
   glFrustum(-wx, wx, -Height, Height, Front_plane, Back_plane);
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar(int newWidth, int newHeight)
{
   Width = newWidth / 10;
   Height = newHeight / 10;
   change_projection(float(newHeight) / float(newWidth));
   glViewport(0, 0, newWidth, newHeight);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef(0.0, 0.0, -Observer_distance);
   glRotatef(Observer_angle_y, 0.0, 1.0, 0.0);
   glRotatef(Observer_angle_x, 1.0, 0.0, 0.0);
}
