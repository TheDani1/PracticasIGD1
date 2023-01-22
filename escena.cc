#include "auxiliar.h" // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

#define EPSILON 0.0001

void Escena::evento(string evento)
{

   using namespace std;

   printf("\033[1;42m");

   std::cout << "[Evento] " << evento << "\033[0m" << endl;

}

void Escena::error(string error)
{

   using namespace std;

   printf("\033[1;41m");

   std::cout << "[×] " << error << "\033[0m" << endl;
}

void Escena::visualizar_menu()
{

   using namespace std;

   switch (modoMenu)
   {
   case NADA:

      cout << "\033[1;35m[MENU PRINCIPAL]\033[0m" << endl
           << "\t\033[1;34m [O]: Activar modo seleccion de objetos\033[0m" << endl
           << "\t\033[1;33m [V]: Activar modo seleccion de modo de visualizacion\033[0m" << endl
           << "\t\033[1;36m [M]: Activar modo movimiento modelo jerarquico\033[0m" << endl
           << "\t\033[1;31m [A]: Activar animacion automatica\033[0m" << endl
           << "\t\033[1;32m [T]: Activar modo iluminacion\033[0m" << endl
           << "\t\033[1;30m [C]: Cambiar cámaras\033[0m" << endl
           << "\t\033[4;30m [Q]: Salir del programa\033[0m" << endl;

      break;

   case SELOBJETO:
      //    0          1        2      3     4       5          6
      //    P          C        E      N     U       Y          L       J         F
      // peon,      cono,    esfera,  peón, cilindro, columna lampara   escultura FOCO
      // cono, escultura, peon, esfera, cilindro, foco, columna, lampara
      cout << "\033[1;34m[MENU SELECCION DE OBJETO]" << endl
           << "\t [C]: Se visualiza/oculta el cono ᐃ" << endl      // h
           << "\t [J]: Se visualiza/oculta la escultura ®" << endl // h
           << "\t [P]: Se visualiza/oculta el peon ♙" << endl      // h
           << "\t [E]: Se visualiza/oculta la esfera ●" << endl
           << "\t [U]: Se visualiza/oculta el cilindro 🗙" << endl
           << "\t [F]: Se visualiza/oculta el foco ⏀" << endl
           << "\t [Y]: Se visualiza/oculta la columna 𐇦" << endl
           << "\t [L]: Se visualiza/oculta la lampara ⚬\033[0m" << endl
           << "\t\033[4;30m [Q]: Salir del [MENU SELECCION DE OBJETO]\033[0m" << endl;

      break;

   case SELVISUALIZACION:

      cout << "\033[1;33m[MENU SELECCION DE MODO DE VISUALIZACION]" << endl
           << "\t [D]: Se activa/desactiva la visualizacion en modo puntos ░" << endl
           << "\t [L]: Se activa/desactiva la visualizacion en modo lineas △ □" << endl
           << "\t [S]: Se activa/desactiva la visualizacion en modo solido (por defecto) ■ ▲" << endl
           << "\t [T]: Se activa la visualización con iluminacion\033[0m" << endl
           << "\t\033[4;30m [Q]: Salir del [MENU SELECCION DE MODO DE VISUALIZACION]\033[0m" << endl;

      break;

   case MOVIMIENTO:

      cout << "\033[1;36m[MENU MOVIMIENTO MODELO JERARQUICO]" << endl
           << "\t [2]: Se selecciona el primer grado de libertad" << endl
           << "\t [3]: Se selecciona el segundo grado de libertad" << endl
           << "\t [4]: Se selecciona el tercer grado de libertad" << endl
           << "\t [+]: Se aumenta el valor" << endl
           << "\t [-]: Se decrementa el valor\033[0m" << endl
           << "\t\033[4;30m [Q]: Salir del [MENU MOVIMIENTO MODELO JERARQUICO]\033[0m" << endl;

      break;

   case ANIMACION:

      cout << "\033[1;31m[MENÚ ANIMACIÓN]" << endl
           << "\t [+]: Aumentar la velocidad de la animacion" << endl
           << "\t [-]: Disminuir la velocidad de la animacion\033[0m" << endl;

      break;

   case LUZ:

      cout << "\033[1;32m[MENÚ LUZ ¤]" << endl
           << "\t [P]: Se anima automáticamente la luz puntual" << endl
           << "\t [D]: Se anima automáticamente el color de la luz direccional\033[0m" << endl
           << "\t\033[4;30m [Q]: Salir del [MENU MOVIMIENTO MODELO JERARQUICO]\033[0m" << endl;

      break;

   case CAMARAS:

      cout << "\033[1;30m[MENÚ CAMARAS ƒ]" << endl
           << "\t [0]: Camara perspectiva" << endl
           << "\t [1]: Ortogonal" << endl
           << "\t [2]: Camara perspectiva\033[0m" << endl
           << "\t\033[4;30m [Q]: Salir del [MENU CÁMARAS ƒ]\033[0m" << endl;

      break;

   default:

      cout << "\033[1;35m[MENU PRINCIPAL]\033[0m" << endl
           << "\t\033[1;34m [O]: Activar modo seleccion de objetos\033[0m" << endl
           << "\t\033[1;33m [V]: Activar modo seleccion de modo de visualizacion\033[0m" << endl
           << "\t\033[1;36m [M]: Activar modo movimiento modelo jerarquico\033[0m" << endl
           << "\t\033[1;31m [A]: Activar animacion automatica\033[0m" << endl
           << "\t\033[1;32m [T]: Activar modo iluminacion\033[0m" << endl
           << "\t\033[4;30m [Q]: Salir del programa\033[0m" << endl;

      break;
   }
}

Escena::Escena()
{

   ejes.changeAxisSize(5000);

   unsigned char *selection_color = new unsigned char[3];
   unsigned char *selection_color2 = new unsigned char[3];
   unsigned char *selection_color3 = new unsigned char[3];


   cono = new Cono(10, 10, 10, 5);

   escultura = new ObjPLY("plys/untitled.ply");

   columna = new ObjPLY("plys/can.ply");
   selection_color3[0] = 255;
   selection_color3[1] = 255;
   selection_color3[2] = 0;
   columna->setColorSeleccion(selection_color3);

   lampara = new ObjPLY("plys/lampara.ply");
   selection_color[0] = 254;
   selection_color[1] = 255;
   selection_color[2] = 255;
   lampara->setColorSeleccion(selection_color);

   peon = new ObjRevolucion("plys/peon_polos.ply", 20, CILINDRICA, true);
   peon->setColorSolido({0.5568627451, 0.6549019608, 0.9137254902});

   esfera = new Esfera(20, 20, 50);

   cilindro = new Cilindro(20, 20, 50, 20);
   
   foco = new Foco();
   selection_color2[0] = 255;
   selection_color2[1] = 0;
   selection_color2[2] = 255;
   foco->setColorSeleccion(selection_color2);

   cuadro = new Cuadro(50);

   cielo = new Esfera(20, 20, 1);
   cielo->invertirCaras();

   // MATERIALES ------------------------------------------------

   Material oro({0.24725, 0.1995, 0.0745, 1}, {0.75164, 0.60648, 0.22648, 1}, {0.628281, 0.555802, 0.366065, 1}, 0.4 * 128.0f);
   Material turquesa({0.1, 0.18725, 0.1745, 1}, {0.396, 0.74151, 0.69102, 1}, {0.297254, 0.30829, 0.306678, 1}, 0.1 * 128.0f);
   Material perla({0.25, 0.20725, 0.20725, 1}, {1, 0.829, 0.829, 1}, {0.296648, 0.296648, 0.296648, 1}, 128.0f * 0.088);
   Material esmeralda({0.0215, 0.1745, 0.0215, 1}, {0.07568, 0.61424, 0.07568, 1}, {0.633, 0.727811, 0.633, 1}, 0.6 * 128.0f);
   Material plata({0.19225, 0.19225, 0.19225, 1}, {0.50754, 0.50754, 0.50754, 1}, {0.508273, 0.508273, 0.508273, 1}, 0.4 * 128.0f);

   Material peon_blanco({1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, 0);

   Material perla_emisiva({0.25, 0.20725, 0.20725, 1}, {1, 0.829, 0.829, 1}, {0.296648, 0.296648, 0.296648, 1}, 128.0f * 0.088);

   perla_emisiva.setEmision({0.988235294, 0.352941176, 0.31372549, 1.0});

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

   if (peon != nullptr)
   {
      peon->setMaterial(peon_blanco);
   }

   if (escultura != nullptr)
   {

      escultura->setMaterial(peon_blanco);
   }

   if (columna != nullptr)
   {

      columna->setMaterial(peon_blanco);
   }

   if (cubo != nullptr)
   {
      cubo->setMaterial(oro);
   }

   if (foco != nullptr)
   {
      foco->setMaterial(oro);
   }

   if (cielo != nullptr)
   {
      cielo->setMaterial(peon_blanco);
   }

   if (lampara != nullptr)
   {

      lampara->setMaterial(oro);
   }

   // TEXTURAS ------------------------------------------------

   cuadro->setTextura("textures/pigscene.jpg");

   cono->setTextura("textures/cono.jpg");

   escultura->setTextura("textures/texture-marmol.jpg");
   columna->setTextura("textures/texture-marmol.jpg");

   esfera->setTextura("textures/8k_sun.jpg");

   cilindro->setTextura("textures/columna.jpg");

   cielo->setTextura("textures/comprimida.jpg");

   lampara->setTextura("textures/metal.jpg");

   foco->setTextura("textures/foco.jpg", "textures/text-madera.jpg", "textures/beam.jpg");

   // LUCES ------------------------------------------------

   Tupla3f pos0 = {200, 150, 200};
   Tupla2f pos1 = {20, 100};

   luz0 = new LuzPosicional(pos0, GL_LIGHT0, {0, 0, 0, 1}, {1, 1, 1, 1}, {1, 1, 1, 1});
   luz1 = new LuzDireccional(pos1, GL_LIGHT1, {1, 1, 1, 1}, {0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f});

   // Cámaras (Práctica 6) ------------------------------------------------

   Tupla3f eye = {0, 150, 250};
   Tupla3f at = {0, 2, 0};
   Tupla3f up = {0, 2, 0};
   Camara c1(eye, at, up, PERSPECTIVA, 50.0, 2000.0);

   eye = {0, 200, 200};
   at = {0, 0, 0};
   up = {0, 1, 0};
   Camara c2(eye, at, up, ORTOGONAL, 50.0, 2000.0);

   eye = {0, 100, 100};
   at = {0, 0, -115};
   up = {0, 1, 0};
   Camara c3(eye, {0, 0, 0}, up, PERSPECTIVA, 50.0, 2000.0);

   camaras.push_back(c1);
   camaras.push_back(c2);
   camaras.push_back(c3);

   camaraActiva = 0;
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

   for (int i = 0; i < camaras.size(); i++)
   {

      camaras[i].setAspect(-UI_window_width / 10);
      camaras[i].setFov(UI_window_width / 10);
      camaras[i].setBottom(-UI_window_height / 10);
      camaras[i].setTop(UI_window_height / 10);
   }

   change_projection();
   glViewport(0, 0, UI_window_width, UI_window_height);

   visualizar_menu();

   perla_emisiva.setEmision({0.988235294, 0.352941176, 0.31372549, 1.0});
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

   // CIELO ------------------------
   glPushMatrix();
   glTranslatef(-500, 0, 0);
   glScalef(1000, 1000, 1000);
   cielo->draw(SOLIDO);
   glPopMatrix();
   // ------------------------------

   // CUADRO -----------------------
   glPushMatrix();
   glTranslatef(-25, 150, 0);
   cuadro->draw(SOLIDO);
   if (visual_obj[0])
   {
      cuadro->draw(PUNTOS);
   }

   if (visual_obj[1])
   {
      cuadro->draw(LINEAS);
   }
   if (visual_obj[2])
   {
      cuadro->draw(SOLIDO);
   }

   if (visual_obj[3])
   {

      glEnable(GL_LIGHTING);
      cuadro->draw(SOLIDO);

      if (luz0 != nullptr)
      {
         glPushMatrix();
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
   glPopMatrix();
   // ------------------------------

   // CONO --------------------------
   if (sel_obj[0])
   {

      glPushMatrix();
      glTranslatef(-50, 0, 125);
      glScalef(5, 5, 5);

      if (visual_obj[0])
      {
         cono->draw(PUNTOS);
      }
      if (visual_obj[1])
      {
         cono->draw(LINEAS);
      }
      if (visual_obj[2])
      {
         if (camaras[camaraActiva].getObjetoSeleccionado() == CONO)
         {
            cono->draw(SELECCIONADO);
         }
         else
         {
            cono->draw(SOLIDO);
         }
      }

      if (visual_obj[3])
      {

         glEnable(GL_LIGHTING);
         if (camaras[camaraActiva].getObjetoSeleccionado() == CONO)
         {
            cono->setMaterial(perla_emisiva);
         }
         else
         {
            cono->setMaterial(oro);
         }
         cono->draw(SOLIDO);

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
      // ESCULTURA (OBJPLY) --------

      glPushMatrix();
      glTranslatef(100, 95, 100);
      glScalef(0.1, 0.1, 0.1);

      if (visual_obj[0])
      {

         escultura->draw(PUNTOS);
      }
      if (visual_obj[1])
      {

         escultura->draw(LINEAS);
      }
      if (visual_obj[2])
      {
         if (camaras[camaraActiva].getObjetoSeleccionado() == ESCULTURA)
         {

            escultura->draw(SELECCIONADO);
         }
         else
         {

            escultura->draw(SOLIDO);
         }
      }

      if (visual_obj[3])
      {

         glEnable(GL_LIGHTING);
         if (camaras[camaraActiva].getObjetoSeleccionado() == ESCULTURA)
         {
            escultura->setMaterial(perla_emisiva);
         }
         else
         {
            escultura->setMaterial(peon_blanco);
         }

         escultura->draw(SOLIDO);

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

      // ---------------------------
   }

   if (sel_obj[2])
   {

      // PEÓN

      glPushMatrix();
      glTranslatef(100, 0, 0);
      glScalef(20, 20, 20);

      if (visual_obj[0])
      {
         peon->draw(PUNTOS);
      }
      if (visual_obj[1])
      {
         peon->draw(LINEAS);
      }
      if (visual_obj[2])
      {
         if (camaras[camaraActiva].getObjetoSeleccionado() == PEON)
         {
            peon->draw(SELECCIONADO);
         }
         else
         {
            peon->draw(SOLIDO);
         }
      }

      if (visual_obj[3])
      {

         glEnable(GL_LIGHTING);
         if (camaras[camaraActiva].getObjetoSeleccionado() == PEON)
         {
            peon->setMaterial(perla_emisiva);
         }
         else
         {
            peon->setMaterial(peon_blanco);
         }
         peon->draw(SOLIDO);

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
      // ESFERA

      glPushMatrix();
      glTranslatef(0, 50, -200);

      if (visual_obj[0])
      {
         esfera->draw(PUNTOS);
      }
      if (visual_obj[1])
      {
         esfera->draw(LINEAS);
      }
      if (visual_obj[2])
      {
         if (camaras[camaraActiva].getObjetoSeleccionado() == ESFERA)
         {
            esfera->draw(SELECCIONADO);
         }
         else
         {
            esfera->draw(SOLIDO);
         }
      }

      if (visual_obj[3])
      {

         glEnable(GL_LIGHTING);
         if (camaras[camaraActiva].getObjetoSeleccionado() == ESFERA)
         {
            esfera->setMaterial(perla_emisiva);
         }
         else
         {
            esfera->setMaterial(oro);
         }
         esfera->draw(SOLIDO);

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
      // CILINDRO

      glPushMatrix();
      glTranslatef(-50, 0, 50);

      if (visual_obj[0])
      {

         cilindro->draw(PUNTOS);
      }
      if (visual_obj[1])
      {

         cilindro->draw(LINEAS);
      }
      if (visual_obj[2])
      {
         if (camaras[camaraActiva].getObjetoSeleccionado() == CILINDRO)
         {

            cilindro->draw(SELECCIONADO);
         }
         else
         {
            cilindro->draw(SOLIDO);
         }
      }

      if (visual_obj[3])
      {

         glEnable(GL_LIGHTING);
         if (camaras[camaraActiva].getObjetoSeleccionado() == CILINDRO)
         {
            cilindro->setMaterial(perla_emisiva);
         }
         else
         {
            cilindro->setMaterial(perla);
         }

         cilindro->draw(SOLIDO);

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
      // MODELO JERARQUICO

      glPushMatrix();
      glTranslatef(-270, 100, 130);
      glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
      glScalef(10, 10, 10);

      if (visual_obj[0])
      {
         foco->draw(PUNTOS);
      }
      if (visual_obj[1])
      {
         foco->draw(LINEAS);
      }
      if (visual_obj[2])
      {
         if (camaras[camaraActiva].getObjetoSeleccionado() == FOCO)
         {

            foco->draw(SELECCIONADO);
         }
         else
         {
            foco->draw(SOLIDO);
         }
      }

      if (visual_obj[3])
      {

         glEnable(GL_LIGHTING);
         if (camaras[camaraActiva].getObjetoSeleccionado() == FOCO)
         {
            foco->setMaterial(perla_emisiva);
         }
         else
         {
            foco->setMaterial(perla);
         }

         foco->draw(SOLIDO);

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

      glPushMatrix();
      glTranslatef(100, 25, 100);
      glScalef(500, 500, 500);

      if (visual_obj[0])
      {
         columna->draw(PUNTOS);
      }

      if (visual_obj[1])
      {
         columna->draw(LINEAS);
      }

      if (visual_obj[2])
      {

         if (camaras[camaraActiva].getObjetoSeleccionado() == COLUMNA)
         {
            columna->draw(SELECCIONADO);
         }
         else
         {

            columna->draw(SOLIDO);
         }
      }

      if (visual_obj[3])
      {

         glEnable(GL_LIGHTING);
         if (camaras[camaraActiva].getObjetoSeleccionado() == COLUMNA)
         {
            columna->setMaterial(perla_emisiva);
         }
         else
         {
            columna->setMaterial(peon_blanco);
         }

         columna->draw(SOLIDO);

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

   if (sel_obj[7])
   {

      glPushMatrix();
      glTranslatef(-50, 90, 70);
      glScalef(0.1, 0.1, 0.1);

      if (visual_obj[0])
      {

         lampara->draw(PUNTOS);
      }
      if (visual_obj[1])
      {
         lampara->draw(LINEAS);
      }
      if (visual_obj[2])
      {
         if (camaras[camaraActiva].getObjetoSeleccionado() == LAMPARA)
         {

            lampara->draw(SELECCIONADO);
         }
         else
         {

            lampara->draw(SOLIDO);
         }
      }

      if (visual_obj[3])
      {

         glEnable(GL_LIGHTING);
         if (camaras[camaraActiva].getObjetoSeleccionado() == CILINDRO)
         {
            lampara->setMaterial(perla_emisiva);
         }
         else
         {
            lampara->setMaterial(oro);
         }

         lampara->draw(SOLIDO);

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
   evento("Tecla pulsada: '" + string(1, tecla) + "'");
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

         // Piramide, cilindro, esfera, peón, cono , escultura y foco (mj)

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
      // SE VISUALIZA cono
   case 'E':

      // SI ESTAMOS EN EL MENU DE SELECCION DE OBJETO
      // bool sel_obj[4] = {true, true, true, true}; // Piramide, cilindro, esfera y peón
      if (modoMenu == SELOBJETO)
      {

         // VISUALIZAMOS ESFERA sel_obj[2]

         sel_obj[3] = !sel_obj[3];

         if (sel_obj[3])
         {
            evento("Se visualiza la esfera ●");
         }
         else
         {
            evento("Se oculta la esfera ●");
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

         sel_obj[2] = !sel_obj[2];

         if (sel_obj[2])
         {
            evento("Se visualiza el peon ♙");
         }
         else
         {
            evento("Se oculta el peon ♙");
         }

         visualizar_menu();
      }
      else if (modoMenu == LUZ)
      {

         animacion_luz = !animacion_luz;

         if (animacion_luz)
         {
            evento("Animacion automatica luz puntual activada");
         }
         else
         {
            evento("Animacion automatica luz puntual desactivada");
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
            evento("Se visualiza el cilindro 🗙");
         }
         else
         {
            evento("Se oculta el cilindro 🗙");
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

         sel_obj[0] = !sel_obj[0];

         if (sel_obj[0])
         {
            evento("Se visualiza el cono ᐃ");
         }
         else
         {
            evento("Se oculta el cono ᐃ");
         }

         visualizar_menu();
      }
      else if (modoMenu == NADA)
      {

         modoMenu = CAMARAS;
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

         sel_obj[6] = !sel_obj[6];

         if (sel_obj[6])
         {
            evento("Se visualiza la columna 𐇦");
         }
         else
         {
            evento("Se oculta la columna 𐇦");
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

         sel_obj[1] = !sel_obj[1];

         if (sel_obj[1])
         {
            evento("Se visualiza la escultura ®");
         }
         else
         {
            evento("Se oculta la escultura ®");
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
      else if (modoMenu == LUZ)
      {

         animacion_color = !animacion_color;

         if (animacion_color)
         {
            evento("Animacion automatica color luz direccional activada");
         }
         else
         {
            evento("Animacion automatica color luz direccional desactivada");
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

      // SE VISUALIZA EL OBJETO MODO LINEAS
   case 'L':

      if (modoMenu == SELOBJETO)
      {

         // VISUALIZAMOS ESFERA sel_obj[2]

         sel_obj[7] = !sel_obj[7];

         if (sel_obj[7])
         {
            evento("Se visualiza la esfera ●");
         }
         else
         {
            evento("Se oculta la esfera ●");
         }

         visualizar_menu();
      }
      else if (modoMenu == SELVISUALIZACION)
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

      if (modoMenu == CAMARAS)
      {
         camaraActiva = 1;
         change_projection();
         change_observer();
         evento("Cambiada cámara activa a 1 (Ortogonal)");
      }

      if (modoMenu == LUZ)
      {
         if (visual_obj[3])
         {
            luz1->activate();
            evento("Activada/desactivada luz 1 (direccional)");
         }
      }

      break;

   case '0':

      if (modoMenu == CAMARAS)
      {
         camaraActiva = 0;
         change_projection();
         change_observer();
         evento("Cambiada cámara activa a 0 (Perspectiva)");
      }

      if (modoMenu == LUZ)
      {
         if (visual_obj[3])
         {
            luz0->activate();
            evento("Activada/desactivada luz 0 (posicional)");
         }
      }

      break;

   case 'M':

      modoMenu = MOVIMIENTO;

      evento("Modo movimiento modelo jerarquico");

      visualizar_menu();

      break;

   case '2':

      if (modoMenu == CAMARAS)
      {
         camaraActiva = 2;
         change_projection();
         change_observer();
         evento("Cambiada cámara activa a 2 (Perspectiva)");
      }

      if (modoMenu == MOVIMIENTO)
      {
         grad_lib[0] = true;
         grad_lib[1] = false;
         grad_lib[2] = false;

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
         error("Seleccion no valida");
      }
      break;

   case '+':

      if (modoMenu == MOVIMIENTO)
      {

         if (grad_lib[0])
         {
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

         if (grad_lib[0])
         {
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

   case 'F':

      if (modoMenu == SELOBJETO)
      {

         // VISUALIZAMOS CILINDRO

         sel_obj[5] = !sel_obj[5];

         if (sel_obj[5])
         {
            evento("Se visualiza el foco ⏀");
         }
         else
         {
            evento("Se oculta el foco ⏀");
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
   }

   return salir;
}
//**************************************************************************

void Escena::teclaEspecial(int Tecla1, int x, int y)
{

   switch (Tecla1)
   {
   case GLUT_KEY_LEFT:
      camaras[camaraActiva].rotarYExaminar(-1 * (M_PI / 180));
      break;
   case GLUT_KEY_RIGHT:
      camaras[camaraActiva].rotarYExaminar(1 * (M_PI / 180));
      break;
   case GLUT_KEY_UP:
      camaras[camaraActiva].rotarXExaminar(-1 * (M_PI / 180));

      break;
   case GLUT_KEY_DOWN:
      camaras[camaraActiva].rotarXExaminar(1 * (M_PI / 180));
      break;
   case 104:
      camaras[camaraActiva].zoom(0.9);
      change_projection();

      break;
   case 105:
      std::cout << "Tecla especial pulsada: " << Tecla1 << std::endl;
      camaras[camaraActiva].zoom(1.1);
      change_projection();

      break;
   }

   // std::cout << Observer_distance << std::endl;

   // change_observer();
}

//**************************************************************************
// Funcion para definir la transformacion de proyeccion
//
// ratio_xy : relaccion de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection()
{
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   camaras[camaraActiva].setProyeccion();
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar(int newWidth, int newHeight)
{
   const float ratio = (float)newWidth / (float)newHeight;

   for (int i = 0; i < camaras.size(); i++)
   {

      camaras[i].setAspect(camaras[i].getBottom() * ratio);
      camaras[i].setFov(camaras[i].getTop() * ratio);
   }

   change_projection();
   glViewport(0, 0, newWidth, newHeight);
}

//**************************************************************************
// Funcion para definir la transformacion de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   
   camaras[camaraActiva].setObserver();

   glGetFloatv(GL_MODELVIEW_MATRIX, mat);
}

void Escena::animarModeloJerarquico()
{

   if (animacion_luz)
   {

      rotacionLuzPuntual += velocidadLuzPuntual;
      rotacionLuzPuntual = fmod(rotacionLuzPuntual, 360.0F);
   }

   if (animacion_color)
   {

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

      if (foco->getGiroZ() > 90)
      {
         velocidadAnimacionZY = velocidadAnimacionZY * -1;
      }
      else if (foco->getGiroZ() < -90)
      {
         velocidadAnimacionZY = velocidadAnimacionZY * -1;
      }

      foco->addGiroZ(velocidadAnimacionZY);
      foco->addGiroY(velocidadAnimacionZY);
   }
}

void Escena::clickRaton(int boton, int estado, int x, int y)
{

   xant = x;
   yant = y;

   if (boton == GLUT_RIGHT_BUTTON)
   {

      if (estado == GLUT_DOWN)
      {
         if (camaras[camaraActiva].getObjetoSeleccionado() == NINGUNO)
         {
            estadoRaton = MOVIENDO_CAMARA_FIRSTPERSON;
         }
         else
         {
            estadoRaton = MOVIENDO_CAMARA_EXAMINAR;
         }
      }
      else
      {
         estadoRaton = NONE;
      }
   }
   else if (boton == GLUT_LEFT_BUTTON)
   {
      if (estado == GLUT_UP)
      {
         dibujaSeleccion();
         processPick(x, y);
      }
   }
   else if (boton == MOUSE_WHEEL_DOWN)
   {
      camaras[camaraActiva].zoom(1.1);
   }
   else if (boton == MOUSE_WHEEL_UP)
   {
      camaras[camaraActiva].zoom(0.9);
   }
   else
   {
      std::cout << "Boton no implementado: " << boton << std::endl;
   }

   change_projection();
}

void Escena::ratonMovido(int x, int y)
{

   if (estadoRaton == MOVIENDO_CAMARA_FIRSTPERSON)
   {
      camaras[camaraActiva].girar(x - xant, y - yant);
      xant = x;
      yant = y;
   }
   else if (estadoRaton == MOVIENDO_CAMARA_EXAMINAR)
   {
      camaras[camaraActiva].girar_examinar(x - xant, y - yant);
      xant = x;
      yant = y;
   }
}

void Escena::dibujaSeleccion()
{
   // Deshabilitamos todo (TEXTURAS, LUCES, DITHER)
   glDisable(GL_DITHER);
   glDisable(GL_LIGHTING);
   glDisable(GL_TEXTURE_2D);

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpiar la pantalla

   change_observer();

   // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

   // bool sel_obj[7] = {true, true, true, false, true, false, false}; // Piramide, cilindro, esfera, peón, cono , escultura y foco (mj)

   if (sel_obj[0])
   {
      
      glPushMatrix();
      glTranslatef(-50, 0, 125);
      glScalef(5, 5, 5);
      cono->draw(SELECCION);
      glPopMatrix();
   }

   if (sel_obj[1])
   {
      glPushMatrix();
      glTranslatef(100, 95, 100);
      glScalef(0.1, 0.1, 0.1);
      escultura->draw(SELECCION);
      glPopMatrix();
   }

   if (sel_obj[2])
   {
      glPushMatrix();
      glTranslatef(100, 0, 0);
      glScalef(20, 20, 20);
      peon->draw(SELECCION);
      glPopMatrix();
   }

   if (sel_obj[3])
   {
      glPushMatrix();
      glTranslatef(0, 50, -200);
      esfera->draw(SELECCION);
      glPopMatrix();
   }

   if (sel_obj[4])
   {
      glPushMatrix();
      glTranslatef(-50, 0, 50);
      cilindro->draw(SELECCION);
      glPopMatrix();
   }

   if (sel_obj[5])
   {
      glPushMatrix();
      glTranslatef(-270, 100, 130);
      glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
      glScalef(10, 10, 10);
      foco->draw(SELECCION);
      glPopMatrix();
   }

   if (sel_obj[6])
   {
      glPushMatrix();
      glTranslatef(100, 25, 100);
      glScalef(500, 500, 500);
      columna->draw(SELECCION);
      glPopMatrix();
   }

   if (sel_obj[7])
   {
      glPushMatrix();
      glTranslatef(-50, 90, 70);
      glScalef(0.1, 0.1, 0.1);
      lampara->draw(SELECCION);
      glPopMatrix();
   }

   glEnable(GL_DITHER);
   glEnable(GL_LIGHTING);
   glEnable(GL_TEXTURE_2D);
}

void Escena::processPick(int x, int y)
{
   glDisable(GL_DITHER);
   glDisable(GL_LIGHTING);
   glDisable(GL_TEXTURE_2D);

   GLint viewport[4];
   GLubyte pixel[3];

   glGetIntegerv(GL_VIEWPORT, viewport);

   glReadPixels(x, viewport[3] - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, (void *)pixel);

   Tupla3i leido = {pixel[0], pixel[1], pixel[2]};

   Tupla3f centro;

   if (leido(0) < EPSILON && leido(1) < EPSILON && leido(2) < EPSILON) // 0 0 0 cono
   {
      evento("Seleccionado cono ᐃ ");
      camaras[camaraActiva].setObjetoSeleccionado(CONO);

      centro = cono->getCentro();

      centro = centroCamara(centro);

      camaras[camaraActiva].setAt(centro);
   }
   else if (leido(0) < EPSILON && leido(1) < EPSILON && leido(2) == 255) // 0 0 1 escultura
   {
      evento("Seleccionada escultura ® ");
      camaras[camaraActiva].setObjetoSeleccionado(ESCULTURA);

      centro = escultura->getCentro();

      centro = centroCamara(centro);

      camaras[camaraActiva].setAt(centro);
   }
   else if (leido(0) < EPSILON && leido(1) == 255 && leido(2) < EPSILON) // 0 1 0 peón
   {
      evento("Seleccionada escultura peon ♙ ");

      camaras[camaraActiva].setObjetoSeleccionado(PEON);

      centro = peon->getCentro();

      centro = centroCamara(centro);

      camaras[camaraActiva].setAt(centro);
   }
   else if (leido(0) < EPSILON && leido(1) == 255 && leido(2) == 255) // 0 1 1 esfera
   {
      evento("Seleccionada esfera ● ");
      camaras[camaraActiva].setObjetoSeleccionado(ESFERA);

      centro = esfera->getCentro();

      centro = centroCamara(centro);

      camaras[camaraActiva].setAt(centro);
   }
   else if (leido(0) == 255 && leido(1) < EPSILON && leido(2) < EPSILON) // 1 0 0 cilindro
   {
      evento("Seleccionado cilindro 🗙 ");
      camaras[camaraActiva].setObjetoSeleccionado(CILINDRO);
      centro = cilindro->getCentro();

      centro = centroCamara(centro);

      camaras[camaraActiva].setAt(centro);
   }
   else if (leido(0) == 255 && leido(1) < EPSILON && leido(2) == 255) // 1 0 1 foco
   {
      evento("Seleccionado foco ⏀ ");
      camaras[camaraActiva].setObjetoSeleccionado(FOCO);

      centro = foco->getCentro();

      centro = centroCamara(centro);

      camaras[camaraActiva].setAt(centro);
   }
   else if (leido(0) == 255 && leido(1) == 255 && leido(2) < EPSILON) // 1 1 0 columna
   {
      evento("Seleccionada columna 𐇦 ");
      camaras[camaraActiva].setObjetoSeleccionado(COLUMNA);

      centro = columna->getCentro();

      centro = centroCamara(centro);

      camaras[camaraActiva].setAt(centro);
   }
   else if (leido(0) == 254 && leido(1) == 255 && leido(2) == 255) // 1 1 1 lampara
   {
      evento("Seleccionada lampara ⚬ ");
      camaras[camaraActiva].setObjetoSeleccionado(LAMPARA);

      centro = lampara->getCentro();

      centro = centroCamara(centro);

      camaras[camaraActiva].setAt(centro);
   }
   else
   {
      error("No se ha seleccionado nada");
      camaras[camaraActiva].setObjetoSeleccionado(NINGUNO);
   }

   glEnable(GL_DITHER);
   glEnable(GL_LIGHTING);
   glEnable(GL_TEXTURE_2D);
}

Tupla3f Escena::centroCamara(const Tupla3f &centro)
{

   Tupla3f n_centro;

   GLfloat inv[16];

   invertMatrix(mat, inv);

   n_centro(0) = inv[0] * centro(0) + inv[4] * centro(1) + inv[8] * centro(2) + inv[12];
   n_centro(1) = inv[1] * centro(0) + inv[5] * centro(1) + inv[9] * centro(2) + inv[13];
   n_centro(2) = inv[2] * centro(0) + inv[6] * centro(1) + inv[10] * centro(2) + inv[14];

   return n_centro;
}

bool Escena::invertMatrix(const float m[16], float invOut[16])
{
   double inv[16], det;
   int i;

   inv[0] = m[5] * m[10] * m[15] -
            m[5] * m[11] * m[14] -
            m[9] * m[6] * m[15] +
            m[9] * m[7] * m[14] +
            m[13] * m[6] * m[11] -
            m[13] * m[7] * m[10];

   inv[4] = -m[4] * m[10] * m[15] +
            m[4] * m[11] * m[14] +
            m[8] * m[6] * m[15] -
            m[8] * m[7] * m[14] -
            m[12] * m[6] * m[11] +
            m[12] * m[7] * m[10];

   inv[8] = m[4] * m[9] * m[15] -
            m[4] * m[11] * m[13] -
            m[8] * m[5] * m[15] +
            m[8] * m[7] * m[13] +
            m[12] * m[5] * m[11] -
            m[12] * m[7] * m[9];

   inv[12] = -m[4] * m[9] * m[14] +
             m[4] * m[10] * m[13] +
             m[8] * m[5] * m[14] -
             m[8] * m[6] * m[13] -
             m[12] * m[5] * m[10] +
             m[12] * m[6] * m[9];

   inv[1] = -m[1] * m[10] * m[15] +
            m[1] * m[11] * m[14] +
            m[9] * m[2] * m[15] -
            m[9] * m[3] * m[14] -
            m[13] * m[2] * m[11] +
            m[13] * m[3] * m[10];

   inv[5] = m[0] * m[10] * m[15] -
            m[0] * m[11] * m[14] -
            m[8] * m[2] * m[15] +
            m[8] * m[3] * m[14] +
            m[12] * m[2] * m[11] -
            m[12] * m[3] * m[10];

   inv[9] = -m[0] * m[9] * m[15] +
            m[0] * m[11] * m[13] +
            m[8] * m[1] * m[15] -
            m[8] * m[3] * m[13] -
            m[12] * m[1] * m[11] +
            m[12] * m[3] * m[9];

   inv[13] = m[0] * m[9] * m[14] -
             m[0] * m[10] * m[13] -
             m[8] * m[1] * m[14] +
             m[8] * m[2] * m[13] +
             m[12] * m[1] * m[10] -
             m[12] * m[2] * m[9];

   inv[2] = m[1] * m[6] * m[15] -
            m[1] * m[7] * m[14] -
            m[5] * m[2] * m[15] +
            m[5] * m[3] * m[14] +
            m[13] * m[2] * m[7] -
            m[13] * m[3] * m[6];

   inv[6] = -m[0] * m[6] * m[15] +
            m[0] * m[7] * m[14] +
            m[4] * m[2] * m[15] -
            m[4] * m[3] * m[14] -
            m[12] * m[2] * m[7] +
            m[12] * m[3] * m[6];

   inv[10] = m[0] * m[5] * m[15] -
             m[0] * m[7] * m[13] -
             m[4] * m[1] * m[15] +
             m[4] * m[3] * m[13] +
             m[12] * m[1] * m[7] -
             m[12] * m[3] * m[5];

   inv[14] = -m[0] * m[5] * m[14] +
             m[0] * m[6] * m[13] +
             m[4] * m[1] * m[14] -
             m[4] * m[2] * m[13] -
             m[12] * m[1] * m[6] +
             m[12] * m[2] * m[5];

   inv[3] = -m[1] * m[6] * m[11] +
            m[1] * m[7] * m[10] +
            m[5] * m[2] * m[11] -
            m[5] * m[3] * m[10] -
            m[9] * m[2] * m[7] +
            m[9] * m[3] * m[6];

   inv[7] = m[0] * m[6] * m[11] -
            m[0] * m[7] * m[10] -
            m[4] * m[2] * m[11] +
            m[4] * m[3] * m[10] +
            m[8] * m[2] * m[7] -
            m[8] * m[3] * m[6];

   inv[11] = -m[0] * m[5] * m[11] +
             m[0] * m[7] * m[9] +
             m[4] * m[1] * m[11] -
             m[4] * m[3] * m[9] -
             m[8] * m[1] * m[7] +
             m[8] * m[3] * m[5];

   inv[15] = m[0] * m[5] * m[10] -
             m[0] * m[6] * m[9] -
             m[4] * m[1] * m[10] +
             m[4] * m[2] * m[9] +
             m[8] * m[1] * m[6] -
             m[8] * m[2] * m[5];

   det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

   if (det == 0)
      return false;

   det = 1.0 / det;

   for (i = 0; i < 16; i++)
      invOut[i] = inv[i] * det;

   return true;
}
