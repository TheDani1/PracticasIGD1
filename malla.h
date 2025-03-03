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

typedef enum {CILINDRICA, ESFERICA, PLANA} tipoTextura;

typedef enum {PUNTOS, LINEAS, SOLIDO, SELECCION, SELECCIONADO} modoVisual;

class Malla3D
{
   public:

   // función que dibuja el objeto en modo diferido (usando VBOs)
   void draw(const modoVisual modo);

   char visual_obj;

   void set_visual(char visual);

   void color_puntos(const Tupla3f color);

   void color_lineas(const Tupla3f color);

   void calcularNormales();

   void setMaterial(const Material &mat);

   void setTextura(const std::string &archivo);

   bool calcularCoordTextura();

   Tupla3f getCentro() const;

   Tupla3f getColorSolido() const;

   unsigned char *getColorSeleccion() const;

   void setColorSolido(const Tupla3f & color);

   void setColorSeleccion(unsigned char selec[3]); 

   void colorear(const modoVisual modo);

   void invertirCaras();

   protected:

      std::vector<Tupla3f> v; // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
      std::vector<Tupla3i> f; // una terna de 3 enteros por cada cara o triángulo

      std::vector<Tupla3f> nv; // tabla de normales

      std::vector<Tupla3f> c_p; // tabla para los colores de los vértices (puntos)
      std::vector<Tupla3f> c_l; // tabla para los colores de los vértices (líneas)
      std::vector<Tupla3u> c_s; // tabla para los colores de los vértices (selección)

      unsigned char *selection_colors;


      std::vector<Tupla2f> ct; // tabla de coordenadas de textura
      Textura textura; // Práctica 5

      // completar P1: tabla de colores (hecho)
      // Completar P1: vbo y método asociado (hecho)

      GLuint id_vbo_tri = 0; // Se inicializa a 0
      GLuint id_vbo_ver = 0; // Se inicializa a 0

      GLuint id_vbo_nv = 0; // Se inicializa a 0

      GLuint id_vbo_c_p = 0; // Se inicializa a 0
      GLuint id_vbo_c_l = 0; // Se inicializa a 0
      GLuint id_vbo_c_s = 0; // Se inicializa a 0

      GLuint id_vbo_ct = 0; // Se inicializa a 0

      Material m; // Práctica 3

      GLuint CrearVBO(GLuint tipo_vbo, GLuint tam, GLvoid *puntero_ram);

      Tupla3f solid_color;
      Tupla3f line_color;
      Tupla3f point_color;

      unsigned char * selection_color = new unsigned char[3];      

		tipoTextura tipotext = PLANA;
      bool coordenadas_textura_creadas = false;

      bool calcular_coordscilindricas();
      bool calcular_coordsesfericas();

      Tupla3f centro_malla;
      void calcular_centro_malla();
      Tupla3f centro_transformado;


} ;

#endif
