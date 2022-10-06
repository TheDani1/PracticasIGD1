#include "auxiliar.h"
#include "malla.h"

// *****************************************************************************
//
// IG_D Clase Malla3D
//
// *****************************************************************************
// -----------------------------------------------------------------------------
// Función de visualización de la malla,

void Malla3D::draw(const GLenum modo)
{
   // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
   // completar (práctica 1)
   // .....

   if (id_vbo_tri == 0)
   {
      id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, f.size() * 3 * sizeof(int), f.data());
   }

   if (id_vbo_ver == 0)
   {
      id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER, 3 * v.size() * sizeof(float), v.data());
   }

   glEnableClientState(GL_COLOR_ARRAY);

   // PUNTOS
   if (modo == GL_POINT)
   {

      if (id_vbo_c_p == 0)
      {
         id_vbo_c_p = CrearVBO(GL_ARRAY_BUFFER, 3 * c_p.size() * sizeof(float), c_p.data());
      }

      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_c_p);
   }

   // LINEAS
   if (modo == GL_LINE)
   {

      if (id_vbo_c_l == 0)
      {
         id_vbo_c_l = CrearVBO(GL_ARRAY_BUFFER, 3 * c_l.size() * sizeof(float), c_l.data());
      }

      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_c_l);
   }

   // SOLIDO
   if (modo == GL_FILL)
   {

      if (id_vbo_c_s == 0)
      {
         id_vbo_c_s = CrearVBO(GL_ARRAY_BUFFER, 3 * c_s.size() * sizeof(float), c_s.data());
      }

      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_c_s);
   }

   // Usar el buffer activo para el color
   glColorPointer(3, GL_FLOAT, 0, 0);

   // desactivar
   glBindBuffer(GL_ARRAY_BUFFER, 0);

   // VERTICES -------------------------------------

   // activar buffer: VBO de vértices
   glBindBuffer(GL_ARRAY_BUFFER, id_vbo_ver);

   // usar como buffer de vertices el actualmente activo
   glVertexPointer(3, GL_FLOAT, 0, 0);

   // desactivar buffer: VBO de vértices.
   glBindBuffer(GL_ARRAY_BUFFER, 0);

   // habilitar el uso de tabla de vértices
   glEnableClientState(GL_VERTEX_ARRAY);

   // activar buffer: VBO de triángulos
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri);

   // dibujar con el buffer de índices activo
   glDrawElements(GL_TRIANGLES, 3 * f.size(), GL_UNSIGNED_INT, 0);

   // desactivar buffer: VBO de triángulos
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

   // desactivar uso de array de vértices
   glDisableClientState(GL_VERTEX_ARRAY);

   //> Javier Melero:
   //¿Tiene sentido estar enviando un vbo cada vez que cambias de color? No

   //> Javier Melero:
   // ¿Cuantos vbo has creado? 3

   //> Javier Melero:
   //¿En algún momento lo sustituyes (suponiendo que sea buena estrategia)?

   //> Javier Melero:
   // piensa que los colores son propiedades de los vértices... no tienes por qué tratarlo de forma diferente
}

void Malla3D::draw_puntos()
{

   // COLORES -------------------------------------
   // AQUI id_vbo_c != 0
   // habilitar uso de array de colores

   // especifícar cual es el VBO que vamos a usar

   
}

void Malla3D::draw_lineas()
{

   // COLORES -------------------------------------
   // AQUI id_vbo_c != 0
   // habilitar uso de array de colores
   glEnableClientState(GL_COLOR_ARRAY);

   // especifícar cual es el VBO que vamos a usar

   // Usar el buffer activo para el color
   glColorPointer(3, GL_FLOAT, 0, 0);

   // desactivar
   glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Malla3D::draw_solido()
{

   // COLORES -------------------------------------
   // AQUI id_vbo_c != 0
   // habilitar uso de array de colores
   glEnableClientState(GL_COLOR_ARRAY);

   // especifícar cual es el VBO que vamos a usar

   // Usar el buffer activo para el color
   glColorPointer(3, GL_FLOAT, 0, 0);

   // desactivar
   glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Malla3D::set_visual(char visual)
{

   visual_obj = visual;
}

// Creación de VBOs
GLuint Malla3D::CrearVBO(GLuint tipo_vbo, GLuint tam, GLvoid *puntero_ram)
{
   GLuint id_vbo; // identificador de VBO

   glGenBuffers(1, &id_vbo); // crear nuevo VBO, obtener identificador

   glBindBuffer(tipo_vbo, id_vbo); // activar el VBO usando su identificador

   // esta instrucción hace la transferencia de datos desde RAM hacia GPU
   glBufferData(tipo_vbo, tam, puntero_ram, GL_STATIC_DRAW);

   glBindBuffer(tipo_vbo, 0); // desactivación del VBO (activar 0)

   return id_vbo;
}

void Malla3D::color_puntos(const Tupla3f color)
{

   for (auto it = c_p.begin(); it != c_p.end(); ++it)
   {
      (*it) = color;
   }
}

void Malla3D::color_lineas(const Tupla3f color)
{

   for (auto it = c_l.begin(); it != c_l.end(); ++it)
   {
      (*it) = color;
   }
}

void Malla3D::color_solido(const Tupla3f color)
{

   for (auto it = c_s.begin(); it != c_s.end(); ++it)
   {
      (*it) = color;
   }
}