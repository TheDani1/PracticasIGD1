// #############################################################################
//
// Informática Gráfica D (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "auxiliar.h"
#include "material.h"
#include "textura.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class Malla3D
{
   public:

   // función que dibuja el objeto en modo diferido (usando VBOs)
   void draw(const GLenum modo);

   char visual_obj;

   void set_visual(char visual);

   void color_puntos(const Tupla3f color);

   void color_lineas(const Tupla3f color);

   void color_solido(const Tupla3f color);

   void calcularNormales();

   void setMaterial(const Material &mat);

   void setTextura()

   protected:

      std::vector<Tupla3f> v; // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
      std::vector<Tupla3i> f; // una terna de 3 enteros por cada cara o triángulo

      std::vector<Tupla3f> nv; // tabla de normales

      std::vector<Tupla3f> c_p; // tabla para los colores de los vértices (puntos)
      std::vector<Tupla3f> c_l; // tabla para los colores de los vértices (líneas)
      std::vector<Tupla3f> c_s; // tabla para los colores de los vértices (sólido)

      std::vector<Tupla2f> ct; // tabla de coordenadas de textura

      Textura *textura = nullptr; // Práctica 5

      // completar P1: tabla de colores (hecho)
      // Completar P1: vbo y método asociado (hecho)

      GLuint id_vbo_tri = 0; // Se inicializa a 0
      GLuint id_vbo_ver = 0; // Se inicializa a 0

      GLuint id_vbo_nv = 0; // Se inicializa a 0

      GLuint id_vbo_c_p = 0; // Se inicializa a 0
      GLuint id_vbo_c_l = 0; // Se inicializa a 0
      GLuint id_vbo_c_s = 0; // Se inicializa a 0

      Material m; // Práctica 3

      GLuint CrearVBO(GLuint tipo_vbo, GLuint tam, GLvoid *puntero_ram);
   
} ;

#endif
