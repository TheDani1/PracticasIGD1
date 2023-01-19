#include "auxiliar.h" // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

void Escena::evento(string evento)
{

   using namespace std;

   printf("\033[1;34m");

   std::cout << "[Evento] " << evento << endl;

   printf("\033[0m");
}

void Escena::error(string error)
{

   using namespace std;

   printf("\033[1;31m");

   std::cout << "[×] " << error << endl;

   printf("\033[0m");
}

void Escena::visualizar_menu()
{

   using namespace std;

   switch (modoMenu)
   {
   case NADA:

      cout << "[MENU PRINCIPAL]" << endl
           << "\t [O]: Activar modo seleccion de objetos" << endl
           << "\t [V]: Activar modo seleccion de modo de visualizacion" << endl
           << "\t [M]: Activar modo movimiento modelo jerarquico" << endl
           << "\t [A]: Activar animacion automatica" << endl
           << "\t [Q]: Salir del programa" << endl;

      break;

   case SELOBJETO:
      //    0          1        2      3     4       5          6
      //    P          C        E      N     U       Y          J
      // Piramide, cilindro, esfera, peón, cubo , hormiga y foco (mj)
      cout << "[MENU SELECCION DE OBJETO]" << endl
           << "\t [P]: Se visualiza/oculta la Piramide △" << endl // h
           << "\t [C]: Se visualiza/oculta el cilindro █" << endl // h
           << "\t [E]: Se visualiza/oculta la Esfera ●" << endl   // h
           << "\t [N]: Se visualiza/oculta el peon ♙" << endl
           << "\t [U]: Se visualiza/oculta el cubo ■" << endl
           << "\t [Y]: Se visualiza/oculta el objeto ply ƒ (hormiga)" << endl
           << "\t [J]: Se visualiza/oculta el modelo jerarquico ¥" << endl
           << "\t [Q]: Salir del [MENU SELECCION DE OBJETO]" << endl;

      break;

   case SELVISUALIZACION:

      cout << "[MENU SELECCION DE MODO DE VISUALIZACION]" << endl
           << "\t [D]: Se activa/desactiva la visualizacion en modo puntos ░" << endl
           << "\t [L]: Se activa/desactiva la visualizacion en modo lineas △ □" << endl
           << "\t [S]: Se activa/desactiva la visualizacion en modo solido (por defecto) ■ ▲" << endl
           << "\t [T]: Se activa la visualización con iluminacion" << endl
           << "\t [Q]: Salir del [MENU SELECCION DE MODO DE VISUALIZACION]" << endl;

      break;

   case MOVIMIENTO:

      cout << "[MENU MOVIMIENTO MODELO JERARQUICO]" << endl
           << "\t [2]: Se selecciona el primer grado de libertad" << endl
           << "\t [3]: Se selecciona el segundo grado de libertad" << endl
           << "\t [4]: Se selecciona el tercer grado de libertad" << endl
           << "\t [+]: Se aumenta el valor" << endl
           << "\t [-]: Se decrementa el valor" << endl
           << "\t [Q]: Salir del [MENU MOVIMIENTO MODELO JERARQUICO]" << endl;

      break;

   case ANIMACION:

      cout << "[MENÚ ANIMACIÓN]" << endl
           << "\t [+]: Aumentar la velocidad de la animacion" << endl
           << "\t [-]: Disminuir la velocidad de la animacion" << endl;

      break;

   case LUZ:

      cout << "[MENÚ LUZ ¤]" << endl
           << "\t [P]: Se anima automáticamente la luz puntual" << endl
           << "\t [D]: Se anima automáticamente el color de la luz direccional" << endl;


      break;

   default:

      cout << "[MENU PRINCIPAL]" << endl
           << "\t [O]: Activar modo seleccion de objetos" << endl
           << "\t [V]: Activar modo seleccion de modo de visualizacion" << endl
           << "\t [M]: Activar modo movimiento modelo jerarquico" << endl
           << "\t [A]: Activar animacion automatica" << endl
           << "\t [Q]: Salir del programa" << endl;

      break;
   }
}

Escena::Escena()
{
   Front_plane = 50.0;
   Back_plane = 2000.0;
   Observer_distance = 4 * Front_plane;
   Observer_angle_x = 0.0;
   Observer_angle_y = 0.0;

   ejes.changeAxisSize(5000);

   // Creación de objetos de la escena

   cubo = new Cubo(50);

   objply = new ObjPLY("plys/ant.ply");

   objrevolucion = new ObjRevolucion("plys/peon_polos.ply", 20, CILINDRICA, true);

   objrevolucion1 = new ObjRevolucion("plys/peon_polos.ply", 20, ESFERICA, true);

   esfera = new Esfera(20, 20, 50);

   cono = new Cono(20, 20, 50, 20);

   cilindro = new Cilindro(20, 20, 50, 20);

   //foco = new Foco();

   cuadro = new Cuadro(50);

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

   if (cilindro != nullptr)
   {
      cilindro->setMaterial(turquesa);
   }

   if (cono != nullptr)
   {
      cono->setMaterial(perla);
   }

   if (objrevolucion != nullptr)
   {
      objrevolucion->setMaterial(peon_blanco);
   }

   if (objrevolucion1 != nullptr)
   {
      objrevolucion1->setMaterial(obsidian);
   }

   if (objply != nullptr)
   {

      objply->setMaterial(esmeralda);
   }

   if(cubo != nullptr){
      cubo->setMaterial(oro);
   }

   if(foco != nullptr){
      foco->setMaterial(oro);
   }

   // TEXTURAS ------------------------------------------------

   string textura = "textures/text-madera.jpg";

   cuadro->setTextura("textures/pigscene.jpg");

   cubo->setTextura(textura);

   //objrevolucion->setTextura(textura);

   //objrevolucion1->setTextura(textura);

   //objply->setTextura(textura);

   esfera->setTextura("textures/textura-tierra.jpg");

   //cono->setTextura(textura);

   cilindro->setTextura("textures/text-lata-1.jpg");
   
   // Como el cuadro se autodefine la textura no hace falta ponerlo   

   // LUCES ------------------------------------------------

   Tupla3f pos0 = {200, 150, 200};
   Tupla2f pos1 = {20, 100};

   luz0 = new LuzPosicional(pos0, GL_LIGHT0, {0, 0, 0, 1}, {1, 1, 1, 1}, {1, 1, 1, 1});
   luz1 = new LuzDireccional(pos1, GL_LIGHT1, {1, 1, 1, 1}, {0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f});
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

   visualizar_menu();
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

   if (sel_obj[0])
   {

      if (visual_obj[0])
      {
         cuadro->draw(GL_POINT);
      }

      if (visual_obj[1])
      {
         cuadro->draw(GL_LINE);
      }
      if (visual_obj[2])
      {
         cuadro->draw(GL_FILL);
      }

      if (visual_obj[3])
      {

         glEnable(GL_LIGHTING);
         cuadro->draw(GL_FILL);

         if (luz0 != nullptr)
         {
            glPushMatrix();
               // std::cout << "Rotacion luz puntual: " << rotacionLuzPuntual << std::endl;
               glRotatef(rotacionLuzPuntual, 0.0f, 1.0f, 0.0f);
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

      //glPopMatrix();
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
      // glScalef(, 20, 20);

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

   if (sel_obj[6])
   {
      // MODELO JERARQUICO

      glPushMatrix();
      // glTranslatef(0, 0, -100);
      glScalef(10, 10, 10);

      if (visual_obj[0])
      {
         foco->draw(GL_POINT);
      }
      if (visual_obj[1])
      {
         foco->draw(GL_LINE);
      }
      if (visual_obj[2])
      {
         foco->draw(GL_FILL);
      }

      if (visual_obj[3])
      {

         glEnable(GL_LIGHTING);
         foco->draw(GL_FILL);

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
         visualizar_menu();
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

         // Piramide, cilindro, esfera, peón, cubo , escultura y foco (mj)

         modoMenu = SELOBJETO;
         visualizar_menu();
      }
      else
      {

         // EN CUALQUIER CASO QUE NO SEA ESE,
         // LA SELECCION NO SERÁ VÁLIDA.

         visualizar_menu();
      }

      break;
   case 'V':
      // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION

      if (modoMenu == NADA)
      {

         // SI NO ESTAMOS EN NINGUN MENU ENTRAMOS EN
         // MENU DE SELECCION DE MODO DE VISUALIZACION.

         modoMenu = SELVISUALIZACION;
         visualizar_menu();
      }
      else
      {

         // EN CUALQUIER CASO QUE NO SEA ESE,
         // LA SELECCION NO SERÁ VÁLIDA.

         error("Seleccion no valida");
         visualizar_menu();
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
            evento("Se visualiza la Esfera ●");
         }
         else
         {
            evento("Se oculta la Esfera ●");
         }

         visualizar_menu();
      }
      else
      {

         // EN CUALQUIER CASO QUE NO SEA ESE,
         // LA SELECCION NO SERÁ VÁLIDA.

         error("Seleccion no valida");
         visualizar_menu();
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
            evento("Se visualiza la piramide △");
         }
         else
         {
            evento("Se oculta la piramide △");
         }

         visualizar_menu();
      }
      else if(modoMenu == LUZ)
      {

         animacion_luz = !animacion_luz;

         if(animacion_luz){
            evento("Animacion automatica luz puntual activada");
         }else{
            evento("Animacion automatica luz puntual desactivada");
         }
         
      }else{

         // EN CUALQUIER CASO QUE NO SEA ESE,
         // LA SELECCION NO SERÁ VÁLIDA.
         error("Seleccion no valida");

         visualizar_menu();

      }

      break;

   case 'N':

      if (modoMenu == SELOBJETO)
      {
         // bool sel_obj[4] = {true, true, true, true}; // Piramide, cilindro, esfera y peón
         // VISUALIZAMOS PEON

         sel_obj[3] = !sel_obj[3];

         if (sel_obj[3])
         {
            evento("Se visualiza el peon ♙");
         }
         else
         {
            evento("Se oculta el peon ♙");
         }

         visualizar_menu();
      }
      else
      {

         // EN CUALQUIER CASO QUE NO SEA ESE,
         // LA SELECCION NO SERÁ VÁLIDA.

         error("Seleccion no valida");

         visualizar_menu();
      }

      break;

   case 'U':

      if (modoMenu == SELOBJETO)
      {
         // bool sel_obj[4] = {true, true, true, true}; // Piramide, cilindro, esfera y peón
         // VISUALIZAMOS PEON

         sel_obj[4] = !sel_obj[4];

         if (sel_obj[4])
         {
            evento("Se visualiza el cubo ■");
         }
         else
         {
            evento("Se oculta el cubo ■");
         }

         visualizar_menu();
      }
      else
      {

         // EN CUALQUIER CASO QUE NO SEA ESE,
         // LA SELECCION NO SERÁ VÁLIDA.

         error("Seleccion no valida");

         visualizar_menu();
      }

      break;

   case 'C':

      if (modoMenu == SELOBJETO)
      {

         // VISUALIZAMOS CILINDRO

         sel_obj[1] = !sel_obj[1];

         if (sel_obj[1])
         {
            evento("Se visualiza el cilindro █");
         }
         else
         {
            evento("Se oculta el cilindro █");
         }

         visualizar_menu();
      }
      else
      {

         // EN CUALQUIER CASO QUE NO SEA ESE,
         // LA SELECCION NO SERÁ VÁLIDA.

         error("Seleccion no valida");

         visualizar_menu();
      }

      break;

   case 'Y':

      if (modoMenu == SELOBJETO)
      {
         // bool sel_obj[4] = {true, true, true, true}; // Piramide, cilindro, esfera y peón
         // VISUALIZAMOS PEON

         sel_obj[5] = !sel_obj[5];

         if (sel_obj[5])
         {
            evento("Se visualiza el objeto ply ƒ");
         }
         else
         {
            evento("Se oculta el objeto ply ƒ");
         }

         visualizar_menu();
      }
      else
      {

         // EN CUALQUIER CASO QUE NO SEA ESE,
         // LA SELECCION NO SERÁ VÁLIDA.

         error("Seleccion no valida");

         visualizar_menu();
      }

      break;

   case 'J':

      if (modoMenu == SELOBJETO)
      {
         // bool sel_obj[4] = {true, true, true, true}; // Piramide, cilindro, esfera y peón
         // VISUALIZAMOS PEON

         sel_obj[6] = !sel_obj[6];

         if (sel_obj[6])
         {
            evento("Se visualiza el modelo jerarquico ¥");
         }
         else
         {
            evento("Se oculta el modelo jerarquico ¥");
         }

         visualizar_menu();
      }
      else
      {

         // EN CUALQUIER CASO QUE NO SEA ESE,
         // LA SELECCION NO SERÁ VÁLIDA.

         error("Seleccion no valida");

         visualizar_menu();
      }

      break;

      // SE VISUALIZA EL OBJETO MODO PUNTOS
   case 'D':

      if (modoMenu == SELVISUALIZACION)
      {

         visual_obj[0] = !visual_obj[0];

         if (visual_obj[0])
         {

            evento("Activado modo puntos");

            visualizar_menu();
         }
         else
         {

            evento("Desactivado modo puntos");

            visualizar_menu();
         }
      }
      else if(modoMenu == LUZ)
      {

         animacion_color = !animacion_color;

         if(animacion_color){
            evento("Animacion automatica color luz direccional activada");
         }else{
            evento("Animacion automatica color luz direccional desactivada");
         }

         
      }else{
         // EN CUALQUIER CASO QUE NO SEA ESE,
         // LA SELECCION NO SERÁ VÁLIDA.

         error("Seleccion no valida");
         visualizar_menu();
      }

      break;

      // SE VISUALIZA EL OBJETO MODO LINEAS
   case 'L':

      if (modoMenu == SELVISUALIZACION)
      {

         visual_obj[1] = !visual_obj[1];

         if (visual_obj[1])
         {

            evento("Activado modo lineas");

            visualizar_menu();
         }
         else
         {

            evento("Desactivado modo lineas");

            visualizar_menu();
         }
      }
      else
      {

         // EN CUALQUIER CASO QUE NO SEA ESE,
         // LA SELECCION NO SERÁ VÁLIDA.

         error("Seleccion no valida");

         visualizar_menu();
      }

      break;

      // SE VISUALIZA EL OBJETO MODO SOLIDO
   case 'S':

      if (modoMenu == SELVISUALIZACION)
      {

         visual_obj[2] = !visual_obj[2];

         if (visual_obj[2])
         {

            evento("Activado modo solido");

            visualizar_menu();
         }
         else
         {

            evento("Desactivado modo solido");

            visualizar_menu();
         }
      }
      else
      {

         // EN CUALQUIER CASO QUE NO SEA ESE,
         // LA SELECCION NO SERÁ VÁLIDA.

         error("Seleccion no valida");

         visualizar_menu();
      }

      break;

   case 'T':

      modoMenu = LUZ;

      visual_obj[3] = !visual_obj[3];

      visual_obj[1] = false;
      visual_obj[2] = false;
      visual_obj[0] = false;

      if (visual_obj[3])
      {

         evento("Activado modo iluminación");

         visualizar_menu();
      }
      else
      {

         evento("Desactivado modo iluminación");

         visualizar_menu();
      }

      break;

   case '1':

      if (modoMenu == LUZ)
      {
         if (visual_obj[3])
         {
            luz1->activate();
         }
      }

      break;

   case '0':

      if (modoMenu == LUZ)
      {
         if (visual_obj[3])
         {
            luz0->activate();
         }
      }

      break;

   case 'M':

      modoMenu = MOVIMIENTO;

      evento("Modo movimiento modelo jerarquico");

      visualizar_menu();

      break;

   case '2':

      grad_lib[0] = true;
      grad_lib[1] = false;
      grad_lib[2] = false;

      if (modoMenu == MOVIMIENTO)
      {

         evento("Seleccionado primer (1) grado de libertad");

         visualizar_menu();
      }
      else
      {
         error("Seleccion no valida");
      }
      break;

   case '3':

      grad_lib[0] = false;
      grad_lib[1] = true;
      grad_lib[2] = false;

      if (modoMenu == MOVIMIENTO)
      {
         evento("Seleccionado segundo (2) grado de libertad");

         visualizar_menu();
      }
      else
      {

         error("Seleccion no valida");
      }

      break;

   case '4':

      grad_lib[0] = false;
      grad_lib[1] = false;
      grad_lib[2] = true;

      if (modoMenu == MOVIMIENTO)
      {

         cout << "[Evento] Seleccionado tercer (3) grado de libertad" << endl;

         evento("Seleccionado tercer (3) grado de libertad");

         visualizar_menu();
      }
      else
      {

         cout << "[!] Seleccion no valida" << endl;
      }
      break;

   case '+':

      if (modoMenu == MOVIMIENTO)
      {

         if (grad_lib[0]){
            foco->addGiroY(1.0);
            evento("Aumentado valor del primer grado de libertad");
         }

         if (grad_lib[1])
         {

            if (foco->getGiroZ() == 90)
            {

               foco->addGiroZ(0);
               error("Limite de 90 alcanzado, no puede incrementar mas");
               
            }
            else
            {

               foco->addGiroZ(1.0);
               evento("Aumentado valor del segundo grado de libertad)");
            }
         }

         if (grad_lib[2])
         {

            if (foco->getTransX() == 17)
            {

               foco->addTransX(0);

               error("Limite de 17 alcanzado, no puede incrementar mas");
            }
            else
            {

               foco->addTransX(1.0);
               evento("Aumentado valor del tercer grado de libertad)");
            }
         }

         

         visualizar_menu();
      }
      else if (modoMenu == ANIMACION)
      {
         velocidadAnimacionX *= 1.2f;
         velocidadAnimacionZY *= 1.2f;
         evento("Aumentada velocidad de animacion");
      }
      else
      {
         error("Seleccion no valida");
      }
      break;

   case '-':

      if (modoMenu == MOVIMIENTO)
      {

         if (grad_lib[0]){
            evento("Decrementado valor del primero grado de libertad");
            foco->addGiroY(-1.0);
         }
         if (grad_lib[1])
         {

            if (foco->getGiroZ() == -90)
            {

               foco->addGiroZ(0);
               error("Limite de -90 alcanzado, no puede decrementar mas");
            }
            else
            {

               foco->addGiroZ(-1.0);
               evento("Decrementado valor del segundo grado de libertad");
            }
         }

         if (grad_lib[2])
         {

            if (foco->getTransX() == -17)
            {

               foco->addTransX(0);

               error("Limite de -17 alcanzado, no puede decrementar mas");
            }
            else
            {

               foco->addTransX(-1.0);
               evento("Decrementado valor del tercer grado de libertad");
            }
         }

         visualizar_menu();
      }
      else if (modoMenu == ANIMACION)
      {

         velocidadAnimacionX *= 0.8f;
         velocidadAnimacionZY *= 0.8f;

         evento("Decrementada velocidad de animacion");
         
      }
      else
      {
         error("Seleccion no valida");
      }
      break;

   case 'A':
      // ENTRAMOS EN MENÚ ANIMACIÓN

      if (modoMenu == NADA)
      {

         // SI NO ESTAMOS EN NINGUN MENU ENTRAMOS EN
         // MENU DE SELECCION DE MODO DE VISUALIZACION.

         animacion = !animacion;

         modoMenu = ANIMACION;
         visualizar_menu();
      }
      else if (modoMenu == ANIMACION)
      {

         animacion = !animacion;

         visualizar_menu();
      }
      else
      {
         error("Seleccion no valida");
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

void Escena::animarModeloJerarquico()
{

   if(animacion_luz){

      rotacionLuzPuntual += velocidadLuzPuntual;
      rotacionLuzPuntual = fmod(rotacionLuzPuntual, 360.0F);

   }

   if(animacion_color){
         
      // std::cout << "Animacion color" << std::endl;
      luz1->variarColorDifuso(factor_aumento);
   
   }

   if (animacion)
   {

      if (foco->getTransX() > 17)
      {
         velocidadAnimacionX = velocidadAnimacionX * -1;
      }
      else if (foco->getTransX() < -17)
      {
         velocidadAnimacionX = velocidadAnimacionX * -1;
      }

      foco->addTransX(velocidadAnimacionX);

      if(foco->getGiroZ() > 90){
         velocidadAnimacionZY = velocidadAnimacionZY * -1;
      }
      else if(foco->getGiroZ() < -90){
         velocidadAnimacionZY = velocidadAnimacionZY * -1;
      }

      foco->addGiroZ(velocidadAnimacionZY);
      foco->addGiroY(velocidadAnimacionZY);
      
   }
}