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

   objply = new ObjPLY("plys/big_dodge.ply");

   objrevolucion = new ObjRevolucion("plys/peon_polos.ply", 20);

   esfera = new Esfera(20, 20, 50);
}

//**************************************************************************
// inicializacion de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyeccion
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
// funcion de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpiar la pantalla
   change_observer();
   ejes.draw();

   //glEnable(GL_CULL_FACE);

   //  COMPLETAR
   //    Dibujar los diferentes elementos de la escena
   //  Habrá que tener en esta primera práctica una variable que indique qué objeto se ha de visualizar
   //  y hacer
   //  cubo->draw()
   //  o    piramide->draw()
   // glPointSize(5);
   // glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

   // objrevolucion->draw(GL_POINT);

   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

   glPushMatrix ();
   glTranslatef(100, 0, 0);
   glScalef(20, 20, 20);
   

   objrevolucion->draw(GL_LINE);

   glPopMatrix();

   esfera->draw(GL_LINE);

   /*if(visual_obj[0]){

      objply->draw(GL_POINT);

   }

   if(visual_obj[1]){

      objply->draw(GL_LINE);

   }

   if(visual_obj[2]){

      objply->draw(GL_FILL);

   }*/

   // if(visual_obj[0]){

   //    glPointSize(5);
   //    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

   //    if(piramide_cubo){

   //       piramide->draw(GL_POINT);

   //    }else{

   //       cubo->draw(GL_POINT);
   //    }

   // }

   // if(visual_obj[1]){

   //    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

   //    if(piramide_cubo){

   //       piramide->draw(GL_LINE);

   //    }else{

   //       cubo->draw(GL_LINE);

   //    }

   // }

   // if(visual_obj[2]){

   //    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

   //    if(piramide_cubo){

   //       piramide->draw(GL_FILL);

   //    }else{

   //       cubo->draw(GL_FILL);
   //    }
   // }
}

//**************************************************************************
//
// funcion que se invoca cuando se pulsa una tecla
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
      if (modoMenu != NADA)
      {
         modoMenu = NADA;
         cout << "[MENU PRINCIPAL]" << endl
              << "\t [O]: Activar modo seleccion de objetos" << endl
              << "\t [V]: Activar modo seleccion de modo de visualizacion" << endl
              << "\t [Q]: Salir del programa" << endl;
      }
      else
      {
         cout << "[EXIT]" << endl;
         salir = true;
      }
      break;
   case 'O':
      // ESTAMOS EN MODO SELECCION DE OBJETO

      if (modoMenu == NADA)
      {

         // SI NO ESTAMOS EN NINGON MENU ENTRAMOS EN
         // MENU DE SELECCION DE OBJETO.

         // △ ▲
         // ■ □
         // △ □
         // ■ ▲

         modoMenu = SELOBJETO;
         cout << "[MENU SELECCION DE OBJETO]" << endl
              << "\t [C]: Se visualiza/oculta el Cubo □" << endl
              << "\t [P]: Se visualiza/oculta la Piramide △" << endl
              << "\t [Q]: Salir del [MENU SELECCION DE OBJETO]" << endl;
      }
      else
      {

         // EN CUALQUIER CASO QUE NO SEA ESE,
         // LA SELECCION NO SERÁ VÁLIDA.

         cout << "[!] Seleccion no valida" << endl;
         cout << "[MENU SELECCION DE OBJETO]" << endl
              << "\t [C]: Se visualiza/oculta el Cubo □" << endl
              << "\t [P]: Se visualiza/oculta la Piramide △" << endl
              << "\t [Q]: Salir del [MENU SELECCION DE OBJETO]" << endl;
      }

      break;
   case 'V':
      // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION

      if (modoMenu == NADA)
      {

         // SI NO ESTAMOS EN NINGUN MENU ENTRAMOS EN
         // MENU DE SELECCION DE MODO DE VISUALIZACION.

         modoMenu = SELVISUALIZACION;
         cout << "[MENU SELECCION DE MODO DE VISUALIZACION]" << endl
              << "\t [D]: Se activa/desactiva la visualizacion en modo puntos ░" << endl
              << "\t [L]: Se activa/desactiva la visualizacion en modo lineas △ □" << endl
              << "\t [S]: Se activa/desactiva la visualizacion en modo solido (por defecto) ■ ▲" << endl
              << "\t [Q]: Salir del [MENU SELECCION DE MODO DE VISUALIZACION]" << endl;
      }
      else
      {

         // EN CUALQUIER CASO QUE NO SEA ESE,
         // LA SELECCION NO SERÁ VÁLIDA.

         cout << "[!] Seleccion no valida" << endl;
         cout << "[MENU SELECCION DE MODO DE VISUALIZACION]" << endl
              << "\t [D]: Se activa/desactiva la visualizacion en modo puntos ░" << endl
              << "\t [L]: Se activa/desactiva la visualizacion en modo lineas △ □" << endl
              << "\t [S]: Se activa/desactiva la visualizacion en modo solido (por defecto) ■ ▲" << endl
              << "\t [Q]: Salir del [MENU SELECCION DE MODO DE VISUALIZACION]" << endl;
      }

      break;

      // COMPLETAR con los diferentes opciones de teclado
      // SE VISUALIZA CUBO
   case 'C':

      // SI ESTAMOS EN EL MENU DE SELECCION DE OBJETO
      if (modoMenu == SELOBJETO)
      {

         // VISUALIZAMOS CUBO

         piramide_cubo = false;

         cout << "[Evento] Visualizando cubo" << endl;

         cout << "[MENU SELECCION DE OBJETO]" << endl
              << "\t [C]: Se visualiza/oculta el Cubo □" << endl
              << "\t [P]: Se visualiza/oculta la Piramide △" << endl
              << "\t [Q]: Salir del [MENU SELECCION DE OBJETO]" << endl;
      }
      else
      {

         // EN CUALQUIER CASO QUE NO SEA ESE,
         // LA SELECCION NO SERÁ VÁLIDA.

         cout << "[!] Seleccion no valida" << endl;
         cout << "[MENU SELECCION DE OBJETO]" << endl
              << "\t [C]: Se visualiza/oculta el Cubo □" << endl
              << "\t [P]: Se visualiza/oculta la Piramide △" << endl
              << "\t [Q]: Salir del [MENU SELECCION DE OBJETO]" << endl;
      }

      break;

      // SE VISUALIZA PIRAMIDE
   case 'P':

      if (modoMenu == SELOBJETO)
      {

         // VISUALIZAMOS PIRAMIDE

         piramide_cubo = true;

         cout << "[Evento] Visualizando piramide" << endl;

         cout << "[MENU SELECCION DE OBJETO]" << endl
              << "\t [C]: Se visualiza/oculta el Cubo □" << endl
              << "\t [P]: Se visualiza/oculta la Piramide △" << endl
              << "\t [Q]: Salir del [MENU SELECCION DE OBJETO]" << endl;
      }
      else
      {

         // EN CUALQUIER CASO QUE NO SEA ESE,
         // LA SELECCION NO SERÁ VÁLIDA.

         cout << "[!] Seleccion no valida" << endl;

         cout << "[MENU SELECCION DE OBJETO]" << endl
              << "\t [C]: Se visualiza/oculta el Cubo □" << endl
              << "\t [P]: Se visualiza/oculta la Piramide △" << endl
              << "\t [Q]: Salir del [MENU SELECCION DE OBJETO]" << endl;
      }

      break;

      // SE VISUALIZA EL OBJETO MODO PUNTOS
   case 'D':

      if (modoMenu == SELVISUALIZACION)
      {

         visual_obj[0] = !visual_obj[0];

         if (visual_obj[0])
         {

            cout << "[Evento] Activado modo puntos" << endl;

            cout << "[MENU SELECCION DE MODO DE VISUALIZACION]" << endl
                 << "\t [D]: Se activa/desactiva la visualizacion en modo puntos ░" << endl
                 << "\t [L]: Se activa/desactiva la visualizacion en modo lineas △ □" << endl
                 << "\t [S]: Se activa/desactiva la visualizacion en modo solido (por defecto) ■ ▲" << endl
                 << "\t [Q]: Salir del [MENU SELECCION DE MODO DE VISUALIZACION]" << endl;
         }
         else
         {

            cout << "[Evento] Desactivado modo puntos" << endl;

            cout << "[MENU SELECCION DE MODO DE VISUALIZACION]" << endl
                 << "\t [D]: Se activa/desactiva la visualizacion en modo puntos ░" << endl
                 << "\t [L]: Se activa/desactiva la visualizacion en modo lineas △ □" << endl
                 << "\t [S]: Se activa/desactiva la visualizacion en modo solido (por defecto) ■ ▲" << endl
                 << "\t [Q]: Salir del [MENU SELECCION DE MODO DE VISUALIZACION]" << endl;
         }
      }
      else
      {

         // EN CUALQUIER CASO QUE NO SEA ESE,
         // LA SELECCION NO SERÁ VÁLIDA.

         cout << "[!] Seleccion no valida" << endl;
         cout << "[MENU SELECCION DE MODO DE VISUALIZACION]" << endl
              << "\t [D]: Se activa/desactiva la visualizacion en modo puntos ░" << endl
              << "\t [L]: Se activa/desactiva la visualizacion en modo lineas △ □" << endl
              << "\t [S]: Se activa/desactiva la visualizacion en modo solido (por defecto) ■ ▲" << endl
              << "\t [Q]: Salir del [MENU SELECCION DE MODO DE VISUALIZACION]" << endl;
      }

      break;

      // SE VISUALIZA EL OBJETO MODO LINEAS
   case 'L':

      if (modoMenu == SELVISUALIZACION)
      {

         visual_obj[1] = !visual_obj[1];

         if (visual_obj[1])
         {

            cout << "[Evento] Modo lineas activado" << endl;

            cout << "[MENU SELECCION DE MODO DE VISUALIZACION]" << endl
                 << "\t [D]: Se activa/desactiva la visualizacion en modo puntos ░" << endl
                 << "\t [L]: Se activa/desactiva la visualizacion en modo lineas △ □" << endl
                 << "\t [S]: Se activa/desactiva la visualizacion en modo solido (por defecto) ■ ▲" << endl
                 << "\t [Q]: Salir del [MENU SELECCION DE MODO DE VISUALIZACION]" << endl;
         }
         else
         {

            cout << "[Evento] Modo lineas desactivado" << endl;

            cout << "[MENU SELECCION DE MODO DE VISUALIZACION]" << endl
                 << "\t [D]: Se activa/desactiva la visualizacion en modo puntos ░" << endl
                 << "\t [L]: Se activa/desactiva la visualizacion en modo lineas △ □" << endl
                 << "\t [S]: Se activa/desactiva la visualizacion en modo solido (por defecto) ■ ▲" << endl
                 << "\t [Q]: Salir del [MENU SELECCION DE MODO DE VISUALIZACION]" << endl;
         }
      }
      else
      {

         // EN CUALQUIER CASO QUE NO SEA ESE,
         // LA SELECCION NO SERÁ VÁLIDA.

         cout << "[!] Seleccion no valida" << endl;

         cout << "[MENU SELECCION DE MODO DE VISUALIZACION]" << endl
              << "\t [D]: Se activa/desactiva la visualizacion en modo puntos ░" << endl
              << "\t [L]: Se activa/desactiva la visualizacion en modo lineas △ □" << endl
              << "\t [S]: Se activa/desactiva la visualizacion en modo solido (por defecto) ■ ▲" << endl
              << "\t [Q]: Salir del [MENU SELECCION DE MODO DE VISUALIZACION]" << endl;
      }

      break;

      // SE VISUALIZA EL OBJETO MODO SOLIDO
   case 'S':

      if (modoMenu == SELVISUALIZACION)
      {

         visual_obj[2] = !visual_obj[2];

         if (visual_obj[2])
         {

            cout << "[Evento] Modo solido activado" << endl;

            cout << "[MENU SELECCION DE MODO DE VISUALIZACION]" << endl
                 << "\t [D]: Se activa/desactiva la visualizacion en modo puntos ░" << endl
                 << "\t [L]: Se activa/desactiva la visualizacion en modo lineas △ □" << endl
                 << "\t [S]: Se activa/desactiva la visualizacion en modo solido (por defecto) ■ ▲" << endl
                 << "\t [Q]: Salir del [MENU SELECCION DE MODO DE VISUALIZACION]" << endl;
         }
         else
         {

            cout << "[Evento] Modo solido desactivado" << endl;

            cout << "[MENU SELECCION DE MODO DE VISUALIZACION]" << endl
                 << "\t [D]: Se activa/desactiva la visualizacion en modo puntos ░" << endl
                 << "\t [L]: Se activa/desactiva la visualizacion en modo lineas △ □" << endl
                 << "\t [S]: Se activa/desactiva la visualizacion en modo solido (por defecto) ■ ▲" << endl
                 << "\t [Q]: Salir del [MENU SELECCION DE MODO DE VISUALIZACION]" << endl;
         }
      }
      else
      {

         // EN CUALQUIER CASO QUE NO SEA ESE,
         // LA SELECCION NO SERÁ VÁLIDA.

         cout << "[!] Seleccion no valida" << endl;

         cout << "[MENU SELECCION DE MODO DE VISUALIZACION]" << endl
              << "\t [D]: Se activa/desactiva la visualizacion en modo puntos ░" << endl
              << "\t [L]: Se activa/desactiva la visualizacion en modo lineas △ □" << endl
              << "\t [S]: Se activa/desactiva la visualizacion en modo solido (por defecto) ■ ▲" << endl
              << "\t [Q]: Salir del [MENU SELECCION DE MODO DE VISUALIZACION]" << endl;
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
// Funcion para definir la transformacion de proyeccion
//
// ratio_xy : relaccion de aspecto del viewport ( == ancho(X) / alto(Y) )
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
// Funcion para definir la transformacion de vista (posicionar la camara)
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
