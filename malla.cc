#include "auxiliar.h"
#include "malla.h"

// *****************************************************************************
//
// IG_D Clase Malla3D
//
// *****************************************************************************
// -----------------------------------------------------------------------------
// Función de visualización de la malla,

#define EPSILON 0.0001

void Malla3D::draw(const modoVisual modo)
{

   if (modo == SELECCION)
   {

      GLfloat mat[16];
      glGetFloatv(GL_MODELVIEW_MATRIX, mat);

      Tupla3f n_centro;

      // aplicamos la transformacion de la matriz al punto
      n_centro(0) = mat[0] * centro_malla(0) + mat[4] * centro_malla(1) + mat[8] * centro_malla(2) + mat[12];
      n_centro(1) = mat[1] * centro_malla(0) + mat[5] * centro_malla(1) + mat[9] * centro_malla(2) + mat[13];
      n_centro(2) = mat[2] * centro_malla(0) + mat[6] * centro_malla(1) + mat[10] * centro_malla(2) + mat[14];

      centro_transformado = n_centro;
   }

   if (!coordenadas_textura_creadas)
   {
      calcularCoordTextura();
   }

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

   if (id_vbo_ct == 0)
   {
      id_vbo_ct = CrearVBO(GL_ARRAY_BUFFER, 2 * ct.size() * sizeof(float), ct.data());
   }

   glEnableClientState(GL_COLOR_ARRAY);

   // PUNTOS
   if (modo == PUNTOS)
   {
      glPointSize(5);
      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
   }

   // LINEAS
   if (modo == LINEAS)
   {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   }

   // SOLIDO
   if (modo == SOLIDO)
   {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   }

   if (modo == SELECCION)
   {

      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

      colorear(modo);
      
      // for(int i = 0 ; i < 128 * 3 * v.size() ; i += 3)
      // {
      //    std::cout << "Color de seleccion(v) " << i << (int) selection_colors[i] << (int) selection_colors[i + 1] << (int) selection_colors[i + 2] << std::endl;
      // }

      if (id_vbo_c_s == 0)
      {
         id_vbo_c_s = CrearVBO(GL_ARRAY_BUFFER, 128 * 3 * v.size(), selection_colors);
      }

      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_c_s);

      // Usar el buffer activo para el color
      glColorPointer(3, GL_UNSIGNED_BYTE, 0, 0);

      // desactivar
      glBindBuffer(GL_ARRAY_BUFFER, 0);
   }
   else if (modo == SELECCIONADO)
   {

      colorear(modo);

      if (id_vbo_c_p == 0)
      {
         id_vbo_c_p = CrearVBO(GL_ARRAY_BUFFER, 3 * c_p.size() * sizeof(float), c_p.data());
      }

      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_c_p);

      // Usar el buffer activo para el color
      glColorPointer(3, GL_FLOAT, 0, 0);

      // desactivar
      glBindBuffer(GL_ARRAY_BUFFER, 0);
   }
   else
   {
      colorear(modo);

      if (id_vbo_c_p == 0)
      {
         id_vbo_c_p = CrearVBO(GL_ARRAY_BUFFER, 3 * c_p.size() * sizeof(float), c_p.data());
      }

      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_c_p);

      // Usar el buffer activo para el color
      glColorPointer(3, GL_FLOAT, 0, 0);

      // desactivar
      glBindBuffer(GL_ARRAY_BUFFER, 0);
   }

   id_vbo_c_p = 0;
   id_vbo_c_s = 0;

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

   if (textura.texturaActivada() && modo != SELECCION)
   {

      glEnable(GL_TEXTURE_2D);
      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_ct);
      glTexCoordPointer(2, GL_FLOAT, 0, 0);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      textura.activar();
   }

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
   glDisableClientState(GL_COLOR_ARRAY);

   if (glIsEnabled(GL_LIGHTING))
   {
      glDisable(GL_NORMALIZE);
      glDisableClientState(GL_NORMAL_ARRAY);
   }

   // TEXTURAS -------------------------------------

   if (textura.texturaActivada())
   {
      glDisableClientState(GL_TEXTURE_COORD_ARRAY);
      glDisable(GL_TEXTURE_2D);
   }
}

void Malla3D::setMaterial(const Material &mat)
{
   m = mat;
}

void Malla3D::setTextura(const std::string &archivo)
{
   textura.crearTextura(archivo);
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

bool Malla3D::calcular_coordscilindricas()
{
   Tupla3f pMax = v[0];

   // Se recorren todos los vértices
   for (int i = 1; i < v.size(); i++)
   {
      if (v[i][0] > pMax[0]) // x
         pMax[0] = v[i][0];

      if (v[i][1] > pMax[1]) // y
         pMax[1] = v[i][1];

      if (v[i][2] > pMax[2]) // z
         pMax[2] = v[i][2];
   }

   Tupla3f pMin = v[0];

   // Se recorren todos los vértices
   for (int i = 1; i < v.size(); i++)
   {
      if (v[i][0] < pMax[0]) // x
         pMax[0] = v[i][0];

      if (v[i][1] < pMax[1]) // y
         pMax[1] = v[i][1];

      if (v[i][2] < pMax[2]) // z
         pMax[2] = v[i][2];
   }

   // Se calcula alfa u y v como indica la teoría
   for (int i = 0; i < v.size(); i++)
   {

      // Se crea alfa
      float alfa = atan2(v[i][2], v[i][0]);

      // u = 0.5 + alfa/2PI
      float u = 0.5 + (alfa / (2 * M_PI));

      // w = altura-altura mínima / altura máxima-altura mínima
      float w = (v[i][1] - pMin[1]) / (pMax[1] - pMin[1]);

      // Se guardan los valores en ct
      ct.push_back(Tupla2f(u, w));
   }

   return true;
}

bool Malla3D::calcularCoordTextura()
{

   if (tipotext == 0)
   {
      calcular_coordscilindricas();
   }
   else if (tipotext == 1)
   {
      calcular_coordsesfericas();
   }
   else
   {
      Tupla3f pMax = v[0];

      // Se recorren todos los vértices
      for (int i = 1; i < v.size(); i++)
      {
         if (v[i][0] > pMax[0]) // x
            pMax[0] = v[i][0];

         if (v[i][1] > pMax[1]) // y
            pMax[1] = v[i][1];

         if (v[i][2] > pMax[2]) // z
            pMax[2] = v[i][2];
      }

      Tupla3f pMin = v[0];

      // Se recorren todos los vértices
      for (int i = 1; i < v.size(); i++)
      {
         if (v[i][0] < pMax[0]) // x
            pMax[0] = v[i][0];

         if (v[i][1] < pMax[1]) // y
            pMax[1] = v[i][1];

         if (v[i][2] < pMax[2]) // z
            pMax[2] = v[i][2];
      }

      for (int i = 0; i < v.size(); i++)
      {
         float u = (v[i][0] - pMin[0]) / (pMax[0] - pMin[0]);

         float w = (v[i][1] - pMin[1]) / (pMax[1] - pMin[1]);

         // Se guardan los valores en ct
         ct.push_back(Tupla2f(u, w));
      }
   }

   return true;
}

bool Malla3D::calcular_coordsesfericas()
{

   float alpha, beta, h;

   float s, t;

   for (int i = 0; i < v.size(); i++)
   {
      alpha = atan2(v[i](2), v[i](0));                                // Cálculo del ángulo en el plano XY
      beta = atan2(v[i](1), sqrt(pow(v[i](0), 2) + pow(v[i](2), 2))); // Cálculo del ángulo en el plano YZ
      s = 1 - (0.5 + (alpha / (M_PI * 2)));                           // Cálculo de la coordenada S
      t = 0.5 + beta / M_PI;                                          // Cálculo de la coordenada T
      // Corrección de costura
      s = fmod(s, 1.0);

      ct.push_back(Tupla2f(s, t));
   }

   return true;
}

void Malla3D::calcular_centro_malla()
{
   for (int i = 0; i < v.size(); i++)
   {
      centro_malla[0] += v[i][0];
      centro_malla[1] += v[i][1];
      centro_malla[2] += v[i][2];
   }

   centro_malla[0] /= v.size();
   centro_malla[1] /= v.size();
   centro_malla[2] /= v.size();
}

Tupla3f Malla3D::getCentro() const
{
   return centro_transformado;
}

Tupla3f Malla3D::getColorSolido() const
{
   return solid_color;
}

unsigned char *Malla3D::getColorSeleccion() const
{
   return selection_color;
}

void Malla3D::setColorSolido(const Tupla3f &color)
{
   solid_color = color;
}

void Malla3D::setColorSeleccion(unsigned char selec[3])
{
   this->selection_color = selec;
}

void Malla3D::colorear(const modoVisual modo)
{
   switch (modo)
   {
   case PUNTOS:
      for (auto it = c_p.begin(); it != c_p.end(); ++it)
      {
         (*it) = point_color;
      }
      break;
   case LINEAS:
      for (auto it = c_p.begin(); it != c_p.end(); ++it)
      {
         (*it) = line_color;
      }
      break;
   case SOLIDO:
      for (auto it = c_p.begin(); it != c_p.end(); ++it)
      {
         (*it) = solid_color;
      }
      break;
   case SELECCION:
   {
      int c = 0;

      for (int i = 0; i < v.size(); i++)
      {
         for (int j = 0; j < 128; j++)
         {
            unsigned char val = 0;

            selection_colors[c + 0] = (unsigned char)selection_color[0];
            selection_colors[c + 1] = (unsigned char)selection_color[1];
            selection_colors[c + 2] = (unsigned char)selection_color[2];

            c += 3;
         }
      }
      break;
   }
   case SELECCIONADO:
   {
      Tupla3f color_real(solid_color(0) - 0.4, solid_color(1) - 0.4, solid_color(2) - 0.4);
      for (auto it = c_p.begin(); it != c_p.end(); ++it)
      {
         (*it) = color_real;
      }
      break;
   }
   default:
      break;
   }
}

void Malla3D::invertirCaras() {
	int tmp;

	for (int i = 0; i < f.size(); i++){
		tmp = f[i](0);
		f[i](0) = f[i](2);
		f[i](2) = tmp;
	}
}
