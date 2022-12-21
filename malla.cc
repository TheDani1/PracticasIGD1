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

   glShadeModel(GL_SMOOTH);

   if (id_vbo_tri == 0)
   {
      id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, f.size() * 3 * sizeof(int), f.data());
   }

   if (id_vbo_ver == 0)
   {
      id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER, 3 * v.size() * sizeof(float), v.data());
   }

   if (id_vbo_nv == 0)
   {

      id_vbo_nv = CrearVBO(GL_ARRAY_BUFFER, 3 * nv.size() * sizeof(float), nv.data());
   }

   if(id_vbo_ct == 0)
   {
      id_vbo_ct = CrearVBO(GL_ARRAY_BUFFER, 2 * ct.size() * sizeof(float), ct.data());
   }

   glEnableClientState(GL_COLOR_ARRAY);

   // PUNTOS
   if (modo == GL_POINT)
   {

      glPointSize(5);
      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

      if (id_vbo_c_p == 0)
      {
         id_vbo_c_p = CrearVBO(GL_ARRAY_BUFFER, 3 * c_p.size() * sizeof(float), c_p.data());
      }

      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_c_p);
   }

   // LINEAS
   if (modo == GL_LINE)
   {

      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

      if (id_vbo_c_l == 0)
      {
         id_vbo_c_l = CrearVBO(GL_ARRAY_BUFFER, 3 * c_l.size() * sizeof(float), c_l.data());
      }

      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_c_l);
   }

   // SOLIDO
   if (modo == GL_FILL)
   {

      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

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

   // NORMALES -------------------------------------

   if (glIsEnabled(GL_LIGHTING))
   {

      glEnableClientState(GL_NORMAL_ARRAY);

      // activar buffer: VBO de normales
      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_nv);

      // usar como buffer de normales el actualmente activo
      glNormalPointer(GL_FLOAT, 0, 0);

      // desactivar buffer: VBO de normales.
      glBindBuffer(GL_ARRAY_BUFFER, 0);

      m.aplicar();
   }


   // Si existen las coordenadas de textura

   // if(!ct.empty())
   // {

   //    textura->activar();

   //    glEnable(GL_TEXTURE_2D);
   //    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
   //    // usar como buffer de coordenadas de textura el actualmente activo
   //    glTexCoordPointer(2, GL_FLOAT, 0, 0);

   // }
   
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

   if (glIsEnabled(GL_LIGHTING))
   {
      glDisableClientState(GL_LIGHTING);
   }

   // TEXTURAS -------------------------------------

   // if (!ct.empty())
   // {
   //    glDisable(GL_TEXTURE_2D);
   //    glDisable(GL_TEXTURE_COORD_ARRAY);
   // }

}

void Malla3D::setMaterial(const Material &mat)
{
   m = mat;
}

void Malla3D::establecerTextura(Textura *text )
{
   textura = text;
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

void Malla3D::calcularNormales()
{

   // Inicializar a cero
   for (int i = 0; i < v.size(); i++)
   {
      nv.push_back(Tupla3f(0, 0, 0));
   }

   // Calcular normales de las caras
   for (int i = 0; i < f.size(); i++)
   {
      Tupla3f v1 = v[f[i](1)] - v[f[i](0)];
      Tupla3f v2 = v[f[i](2)] - v[f[i](0)];

      Tupla3f normal = v1.cross(v2);

      nv[f[i](0)] = nv[f[i](0)] + normal;
      nv[f[i](1)] = nv[f[i](1)] + normal;
      nv[f[i](2)] = nv[f[i](2)] + normal;
   }

   // Normalizar
   for (int i = 0; i < nv.size(); i++)
   {
      nv[i] = nv[i].normalized();
   }
}
