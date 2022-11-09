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

   //piramide = new PiramidePentagonal(50, 50);

   std::cout << "[Coche]" << std::endl;
   objply = new ObjPLY("plys/big_dodge.ply");

   std::cout << "[Peon]" << std::endl;
   objrevolucion = new ObjRevolucion("plys/peon_polos.ply", 20);

   std::cout << "[Peon 2]" << std::endl;
   objrevolucion1 = new ObjRevolucion("plys/peon.ply", 20);

   std::cout << "[Esfera]" << std::endl;
   esfera = new Esfera(20, 20, 50);

   std::cout << "[Cono]" << std::endl;
   cono = new Cono(20, 20, 50, 20);

   std::cout << "[Cilindro]" << std::endl;
   cilindro = new Cilindro(20, 20, 50, 20);

   // MATERIALES ------------------------------------------------

   Material oro({0.24725, 0.1995, 0.0745, 1}, {0.75164, 0.60648, 0.22648, 1}, {0.628281, 0.555802, 0.366065, 1}, 0.4 * 128.0f);
   Material turquesa({0.1, 0.18725, 0.1745, 1}, {0.396, 0.74151, 0.69102, 1}, {0.297254, 0.30829, 0.306678, 1}, 0.1 * 128.0f);
   Material perla({0.25, 0.20725, 0.20725, 1}, {1, 0.829, 0.829, 1}, {0.296648, 0.296648, 0.296648, 1}, 128.0f * 0.088);
   Material esmeralda({0.0215, 0.1745, 0.0215, 1}, {0.07568, 0.61424, 0.07568, 1}, {0.633, 0.727811, 0.633, 1}, 0.6 * 128.0f);

   Material peon_blanco({1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, 0);

   // Material especular sin apenas reflectividad difusa

   //                   difusion               especular        ambiente           brillo
   Material peon_negro({0.1, 0.1, 0.1, 1}, {0.1, 0.1, 0.1, 1}, {0.1, 0.1, 0.1, 1}, 1 * 128.0f);

   Material obsidian({0.05375, 0.05, 0.06625, 1}, {0.18275, 0.17, 0.22525, 1}, {0.332741, 0.328634, 0.346435, 1}, 0.3 * 128.0f);

   if (esfera != nullptr)
   {
      esfera->setMaterial(oro);
   }

   if(cilindro != nullptr)
   {
      cilindro->setMaterial(turquesa);
   }

   if(cono != nullptr)
   {
      cono->setMaterial(perla);
   }

   if(objrevolucion != nullptr)
   {
      objrevolucion->setMaterial(peon_blanco);
   }

   if(objrevolucion1 != nullptr)
   {
      objrevolucion1->setMaterial(obsidian);
   }

   if(objply != nullptr){

      objply->setMaterial(esmeralda);
   }

   // LUCES ------------------------------------------------

   Tupla2f pos0 = {20, 100};
   Tupla2f pos1 = {20, 100};

   luz0 = new LuzPosicional(pos0, GL_LIGHT0, {0, 0, 0, 1}, {1, 1, 1, 1}, {1, 1, 1, 1});
   luz1 = new LuzDireccional(pos1, GL_LIGHT1, {0, 0, 0, 1}, {1, 1, 1, 1}, {1, 1, 1, 1});
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

   glEnable(GL_CULL_FACE);

   glEnable(GL_NORMALIZE);

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
   

   glDisable(GL_LIGHTING);

   ejes.draw();

   // if (visual_obj[3])
   // {
   //    glEnable(GL_LIGHTING);
   //    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

   //    if (luz0 != nullptr)
   //    {
   //       glPushMatrix();
   //       luz0->activar();
   //       glPopMatrix();
   //    }

   //    if (luz1 != nullptr)
   //    {
   //       luz1->activar();
   //    }

   //    esfera->draw(GL_FILL);

   // }

   //  COMPLETAR
   //    Dibujar los diferentes elementos de la escena
   //  Habrá que tener en esta primera práctica una variable que indique qué objeto se ha de visualizar
   //  y hacer
   //  cubo->draw()
   //  o    piramide->draw()
   // glPointSize(5);
   // glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

   if (sel_obj[0])
   {

      // PIRAMIDE

      glPushMatrix();
      glTranslatef(-100, 0, 0);

      if (visual_obj[0])
      {
         cono->draw(GL_POINT);
      }

      if (visual_obj[1])
      {
         cono->draw(GL_LINE);
      }
      if (visual_obj[2])
      {
         cono->draw(GL_FILL);
      }

      if (visual_obj[3])
      {

         glEnable(GL_LIGHTING);
         cono->draw(GL_FILL);

         if (luz0 != nullptr)
         {
            glPushMatrix();
            luz0->activar();
            glPopMatrix();

         }

         if (luz1 != nullptr)
         {
            glPushMatrix();
            luz1->activar();
            glPopMatrix();

         }

      }

      glPopMatrix();
   }

   if (sel_obj[1])
   {

      // CILINDRO

      glPushMatrix();
      glTranslatef(0, 0, 100);

      if (visual_obj[0])
      {
         cilindro->draw(GL_POINT);
      }
      if (visual_obj[1])
      {
         cilindro->draw(GL_LINE);
      }
      if (visual_obj[2])
      {
         cilindro->draw(GL_FILL);
      }

      if (visual_obj[3])
      {

         glEnable(GL_LIGHTING);
         cilindro->draw(GL_FILL);

         if (luz0 != nullptr)
         {
            glPushMatrix();
            luz0->activar();
            glPopMatrix();

         }

         if (luz1 != nullptr)
         {
            glPushMatrix();
            luz1->activar();
            glPopMatrix();

         }

      }

      glPopMatrix();
   }

   if (sel_obj[2])
   {

      // ESFERA

      if (visual_obj[0])
      {
         esfera->draw(GL_POINT);
      }
      if (visual_obj[1])
      {
         esfera->draw(GL_LINE);
      }
      if (visual_obj[2])
      {
         esfera->draw(GL_FILL);
      }


      if (visual_obj[3])
      {

         glEnable(GL_LIGHTING);
         esfera->draw(GL_FILL);

         if (luz0 != nullptr)
         {
            glPushMatrix();
            luz0->activar();
            glPopMatrix();

         }

         if (luz1 != nullptr)
         {
            glPushMatrix();
            luz1->activar();
            glPopMatrix();

         }


      }
   }

   if (sel_obj[3])
   {
      // PEÓN

      glPushMatrix();
      glTranslatef(100, 0, 0);
      glScalef(20, 20, 20);

      if (visual_obj[0])
      {
         objrevolucion->draw(GL_POINT);
      }
      if (visual_obj[1])
      {
         objrevolucion->draw(GL_LINE);
      }
      if (visual_obj[2])
      {
         objrevolucion->draw(GL_FILL);
      }

      if (visual_obj[3])
      {

         glEnable(GL_LIGHTING);
         objrevolucion->draw(GL_FILL);

         if (luz0 != nullptr)
         {
            glPushMatrix();
            luz0->activar();
            glPopMatrix();

         }

         if (luz1 != nullptr)
         {
            glPushMatrix();
            luz1->activar();
            glPopMatrix();

         }

      }

      glPopMatrix();
   }

   if (sel_obj[3])
   {
      // PEÓN 2

      glPushMatrix();
      glTranslatef(100, 0, 50);
      glScalef(20, 20, 20);

      if (visual_obj[0])
      {
         objrevolucion1->draw(GL_POINT);
      }
      if (visual_obj[1])
      {
         objrevolucion1->draw(GL_LINE);
      }
      if (visual_obj[2])
      {
         objrevolucion1->draw(GL_FILL);
      }

      if (visual_obj[3])
      {

         glEnable(GL_LIGHTING);
         objrevolucion1->draw(GL_FILL);

         if (luz0 != nullptr)
         {
            glPushMatrix();
            luz0->activar();
            glPopMatrix();

         }

         if (luz1 != nullptr)
         {
            glPushMatrix();
            luz1->activar();
            glPopMatrix();

         }

      }

      glPopMatrix();
   }

   if (sel_obj[4])
   {
      // CUBO

      glPushMatrix();
      glTranslatef(-100, 0, 50);
      //glScalef(, 20, 20);

      if (visual_obj[0])
      {
         cubo->draw(GL_POINT);
      }
      if (visual_obj[1])
      {
         cubo->draw(GL_LINE);
      }
      if (visual_obj[2])
      {
         cubo->draw(GL_FILL);
      }

      if (visual_obj[3])
      {

         glEnable(GL_LIGHTING);
         cubo->draw(GL_FILL);

         if (luz0 != nullptr)
         {
            glPushMatrix();
            luz0->activar();
            glPopMatrix();

         }

         if (luz1 != nullptr)
         {
            glPushMatrix();
            luz1->activar();
            glPopMatrix();

         }

      }

      glPopMatrix();
   }

   if (sel_obj[5])
   {
      // OBJETO PLY

      glPushMatrix();
      glTranslatef(0, 0, -100);
      glScalef(10, 10, 10);

      if (visual_obj[0])
      {
         objply->draw(GL_POINT);
      }
      if (visual_obj[1])
      {
         objply->draw(GL_LINE);
      }
      if (visual_obj[2])
      {
         objply->draw(GL_FILL);
      }

      if (visual_obj[3])
      {

         glEnable(GL_LIGHTING);
         objply->draw(GL_FILL);

         if (luz0 != nullptr)
         {
            glPushMatrix();
            luz0->activar();
            glPopMatrix();

         }

         if (luz1 != nullptr)
         {
            glPushMatrix();
            luz1->activar();
            glPopMatrix();

         }

      }

      glPopMatrix();
   }
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
         // ▲ ♙ █ ●

         modoMenu = SELOBJETO;
         cout << "[MENU SELECCION DE OBJETO]" << endl
              << "\t [E]: Se visualiza/oculta el Esfera ●" << endl
              << "\t [P]: Se visualiza/oculta la Piramide △" << endl
              << "\t [Z]: Se visualiza/oculta el peon ♙" << endl
              << "\t [C]: Se visualiza/oculta el cilindro █" << endl
              << "\t [Q]: Salir del [MENU SELECCION DE OBJETO]" << endl;
      }
      else
      {

         // EN CUALQUIER CASO QUE NO SEA ESE,
         // LA SELECCION NO SERÁ VÁLIDA.

         cout << "[MENU SELECCION DE OBJETO]" << endl
              << "\t [E]: Se visualiza/oculta el Esfera ●" << endl
              << "\t [P]: Se visualiza/oculta la Piramide △" << endl
              << "\t [Z]: Se visualiza/oculta el peon ♙" << endl
              << "\t [C]: Se visualiza/oculta el cilindro █" << endl
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
              << "\t [T]: Se activa la visualización con iluminacion" << endl
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
              << "\t [T]: Se activa la visualización con iluminacion" << endl
              << "\t [Q]: Salir del [MENU SELECCION DE MODO DE VISUALIZACION]" << endl;
      }

      break;

      // COMPLETAR con los diferentes opciones de teclado
      // SE VISUALIZA CUBO
   case 'E':

      // SI ESTAMOS EN EL MENU DE SELECCION DE OBJETO
      // bool sel_obj[4] = {true, true, true, true}; // Piramide, cilindro, esfera y peón
      if (modoMenu == SELOBJETO)
      {

         // VISUALIZAMOS ESFERA sel_obj[2]

         sel_obj[2] = !sel_obj[2];

         if (sel_obj[2])
         {
            cout << "[!] Se visualiza el Esfera ●" << endl;
         }
         else
         {
            cout << "[!] Se oculta el Esfera ●" << endl;
         }

         cout << "[Evento] Visualizando cubo" << endl;

         cout << "[MENU SELECCION DE OBJETO]" << endl
              << "\t [E]: Se visualiza/oculta el Esfera ●" << endl
              << "\t [P]: Se visualiza/oculta la Piramide △" << endl
              << "\t [Z]: Se visualiza/oculta el peon ♙" << endl
              << "\t [C]: Se visualiza/oculta el cilindro █" << endl
              << "\t [Q]: Salir del [MENU SELECCION DE OBJETO]" << endl;
      }
      else
      {

         // EN CUALQUIER CASO QUE NO SEA ESE,
         // LA SELECCION NO SERÁ VÁLIDA.

         cout << "[!] Seleccion no valida" << endl;
         cout << "[MENU SELECCION DE OBJETO]" << endl
              << "\t [E]: Se visualiza/oculta el Esfera ●" << endl
              << "\t [P]: Se visualiza/oculta la Piramide △" << endl
              << "\t [Z]: Se visualiza/oculta el peon ♙" << endl
              << "\t [C]: Se visualiza/oculta el cilindro █" << endl
              << "\t [Q]: Salir del [MENU SELECCION DE OBJETO]" << endl;
      }

      break;

      // SE VISUALIZA PIRAMIDE
   case 'P':

      if (modoMenu == SELOBJETO)
      {

         // bool sel_obj[4] = {true, true, true, true}; // Piramide, cilindro, esfera y peón

         // VISUALIZAMOS PIRAMIDE

         sel_obj[0] = !sel_obj[0];

         if (sel_obj[0])
         {
            cout << "[!] Se visualiza la Piramide △" << endl;
         }
         else
         {
            cout << "[!] Se oculta la Piramide △" << endl;
         }

         cout << "[MENU SELECCION DE OBJETO]" << endl
              << "\t [E]: Se visualiza/oculta el Esfera ●" << endl
              << "\t [P]: Se visualiza/oculta la Piramide △" << endl
              << "\t [Z]: Se visualiza/oculta el peon ♙" << endl
              << "\t [C]: Se visualiza/oculta el cilindro █" << endl
              << "\t [Q]: Salir del [MENU SELECCION DE OBJETO]" << endl;
      }
      else
      {

         // EN CUALQUIER CASO QUE NO SEA ESE,
         // LA SELECCION NO SERÁ VÁLIDA.

         cout << "[!] Seleccion no valida" << endl;

         cout << "[MENU SELECCION DE OBJETO]" << endl
              << "\t [E]: Se visualiza/oculta el Esfera ●" << endl
              << "\t [P]: Se visualiza/oculta la Piramide △" << endl
              << "\t [Z]: Se visualiza/oculta el peon ♙" << endl
              << "\t [C]: Se visualiza/oculta el cilindro █" << endl
              << "\t [Q]: Salir del [MENU SELECCION DE OBJETO]" << endl;
      }

      break;

   case 'Z':

      if (modoMenu == SELOBJETO)
      {
         // bool sel_obj[4] = {true, true, true, true}; // Piramide, cilindro, esfera y peón
         // VISUALIZAMOS PEON

         sel_obj[3] = !sel_obj[3];

         if (sel_obj[3])
         {
            cout << "[!] Se visualiza el peon ♙" << endl;
         }
         else
         {
            cout << "[!] Se oculta el peon ♙" << endl;
         }

         cout << "[MENU SELECCION DE OBJETO]" << endl
              << "\t [E]: Se visualiza/oculta el Esfera ●" << endl
              << "\t [P]: Se visualiza/oculta la Piramide △" << endl
              << "\t [Z]: Se visualiza/oculta el peon ♙" << endl
              << "\t [C]: Se visualiza/oculta el cilindro █" << endl
              << "\t [Q]: Salir del [MENU SELECCION DE OBJETO]" << endl;
      }
      else
      {

         // EN CUALQUIER CASO QUE NO SEA ESE,
         // LA SELECCION NO SERÁ VÁLIDA.

         cout << "[!] Seleccion no valida" << endl;

         cout << "[MENU SELECCION DE OBJETO]" << endl
              << "\t [E]: Se visualiza/oculta el Esfera ●" << endl
              << "\t [P]: Se visualiza/oculta la Piramide △" << endl
              << "\t [Z]: Se visualiza/oculta el peon ♙" << endl
              << "\t [C]: Se visualiza/oculta el cilindro █" << endl
              << "\t [Q]: Salir del [MENU SELECCION DE OBJETO]" << endl;
      }

      break;

   case 'C':

      if (modoMenu == SELOBJETO)
      {

         // VISUALIZAMOS CILINDRO

         sel_obj[1] = !sel_obj[1];

         if (sel_obj[1])
         {
            cout << "[!] Se visualiza el cilindro █" << endl;
         }
         else
         {
            cout << "[!] Se oculta el cilindro █" << endl;
         }

         cout << "[Evento] Visualizando piramide" << endl;

         cout << "[MENU SELECCION DE OBJETO]" << endl
              << "\t [E]: Se visualiza/oculta el Esfera ●" << endl
              << "\t [P]: Se visualiza/oculta la Piramide △" << endl
              << "\t [Z]: Se visualiza/oculta el peon ♙" << endl
              << "\t [C]: Se visualiza/oculta el cilindro █" << endl
              << "\t [Q]: Salir del [MENU SELECCION DE OBJETO]" << endl;
      }
      else
      {

         // EN CUALQUIER CASO QUE NO SEA ESE,
         // LA SELECCION NO SERÁ VÁLIDA.

         cout << "[!] Seleccion no valida" << endl;

         cout << "[MENU SELECCION DE OBJETO]" << endl
              << "\t [E]: Se visualiza/oculta el Esfera ●" << endl
              << "\t [P]: Se visualiza/oculta la Piramide △" << endl
              << "\t [Z]: Se visualiza/oculta el peon ♙" << endl
              << "\t [C]: Se visualiza/oculta el cilindro █" << endl
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
                 << "\t [T]: Se activa la visualización con iluminacion" << endl
                 << "\t [Q]: Salir del [MENU SELECCION DE MODO DE VISUALIZACION]" << endl;
         }
         else
         {

            cout << "[Evento] Desactivado modo puntos" << endl;

            cout << "[MENU SELECCION DE MODO DE VISUALIZACION]" << endl
                 << "\t [D]: Se activa/desactiva la visualizacion en modo puntos ░" << endl
                 << "\t [L]: Se activa/desactiva la visualizacion en modo lineas △ □" << endl
                 << "\t [S]: Se activa/desactiva la visualizacion en modo solido (por defecto) ■ ▲" << endl
                 << "\t [T]: Se activa la visualización con iluminacion" << endl
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
              << "\t [T]: Se activa la visualización con iluminacion" << endl
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
                 << "\t [T]: Se activa la visualización con iluminacion" << endl
                 << "\t [Q]: Salir del [MENU SELECCION DE MODO DE VISUALIZACION]" << endl;
         }
         else
         {

            cout << "[Evento] Modo lineas desactivado" << endl;

            cout << "[MENU SELECCION DE MODO DE VISUALIZACION]" << endl
                 << "\t [D]: Se activa/desactiva la visualizacion en modo puntos ░" << endl
                 << "\t [L]: Se activa/desactiva la visualizacion en modo lineas △ □" << endl
                 << "\t [S]: Se activa/desactiva la visualizacion en modo solido (por defecto) ■ ▲" << endl
                 << "\t [T]: Se activa la visualización con iluminacion" << endl
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
              << "\t [T]: Se activa la visualización con iluminacion" << endl
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
                 << "\t [T]: Se activa la visualización con iluminacion" << endl
                 << "\t [Q]: Salir del [MENU SELECCION DE MODO DE VISUALIZACION]" << endl;
         }
         else
         {

            cout << "[Evento] Modo solido desactivado" << endl;

            cout << "[MENU SELECCION DE MODO DE VISUALIZACION]" << endl
                 << "\t [D]: Se activa/desactiva la visualizacion en modo puntos ░" << endl
                 << "\t [L]: Se activa/desactiva la visualizacion en modo lineas △ □" << endl
                 << "\t [S]: Se activa/desactiva la visualizacion en modo solido (por defecto) ■ ▲" << endl
                 << "\t [T]: Se activa la visualización con iluminacion" << endl
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
              << "\t [T]: Se activa la visualización con iluminacion" << endl
              << "\t [Q]: Salir del [MENU SELECCION DE MODO DE VISUALIZACION]" << endl;
      }

      break;

   case 'T':

      visual_obj[3] = !visual_obj[3];

      visual_obj[1] = false;
      visual_obj[2] = false;
      visual_obj[0] = false;

      if (visual_obj[3])
      {

         cout << "[Evento] Modo iluminación activado" << endl;

         cout << "[MENU SELECCION DE MODO DE VISUALIZACION]" << endl
              << "\t [D]: Se activa/desactiva la visualizacion en modo puntos ░" << endl
              << "\t [L]: Se activa/desactiva la visualizacion en modo lineas △ □" << endl
              << "\t [S]: Se activa/desactiva la visualizacion en modo solido (por defecto) ■ ▲" << endl
              << "\t [T]: Se activa la visualización con iluminacion" << endl
              << "\t [Q]: Salir del [MENU SELECCION DE MODO DE VISUALIZACION]" << endl;
      }
      else
      {

         cout << "[Evento] Modo solido desactivado" << endl;

         cout << "[MENU SELECCION DE MODO DE VISUALIZACION]" << endl
              << "\t [D]: Se activa/desactiva la visualizacion en modo puntos ░" << endl
              << "\t [L]: Se activa/desactiva la visualizacion en modo lineas △ □" << endl
              << "\t [S]: Se activa/desactiva la visualizacion en modo solido (por defecto) ■ ▲" << endl
              << "\t [T]: Se activa la visualización con iluminacion" << endl
              << "\t [Q]: Salir del [MENU SELECCION DE MODO DE VISUALIZACION]" << endl;
      }

      break;

   case '1':

      if (modoMenu == SELVISUALIZACION)
      {
         if (visual_obj[3])
         {
            luz1->activate();
         }
      }

      break;

   case '0':

      if (modoMenu == SELVISUALIZACION)
      {
         if (visual_obj[3])
         {
            luz0->activate();
         }
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
