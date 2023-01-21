#include "objply.h"
#include "ply_reader.h"

// *****************************************************************************
//
// Clase ObjPLY (práctica 2)
//
// *****************************************************************************

ObjPLY::ObjPLY(const std::string &nombre_archivo)
{
   // leer la lista de caras y vértices
   ply::read(nombre_archivo, this->v, this->f);

   c_p.resize(v.size());
   c_l.resize(v.size());
   c_s.resize(v.size());

   Tupla3f rojo(1, 0, 0);
   Tupla3f verde(0, 1, 0);
   Tupla3f azul(0, 0, 1);

   Tupla3f blanco(0.9f, 0.9f, 0.9f);

   Tupla3f negro(0.0f, 0.0f, 0.0f);

   // color_puntos(rojo);

   // color_lineas(verde);

   // color_solido(blanco);

   point_color = rojo;

   line_color = verde;

   solid_color = blanco;

   selection_colors = new unsigned char[128 * 3 * v.size()];

   coordenadas_textura_creadas = false;

   selection_color[0] = 0;
   selection_color[1] = 0;
   selection_color[2] = 255;

   tipotext = ESFERICA;

   // Tupla3u amarillo(255, 255, 0);

   // selection_color = amarillo;

   calcularNormales();

   calcular_centro_malla();
}
