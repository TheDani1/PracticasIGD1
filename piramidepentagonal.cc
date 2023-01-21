#include "auxiliar.h"
#include "malla.h"
#include "piramidepentagonal.h"

PiramidePentagonal::PiramidePentagonal(float h, float r)
{
   // VÉRTICE DE ATRÁS (base)
   Tupla3f c0(0.0f, 0.0f, -r * sqrt(3) / 2);

   // VÉRTICE LATERALES (base)
   Tupla3f c1(r, 0.0f, 0.0f);
   Tupla3f c2(-r, 0.0f, 0.0f);

   // Parte delantera de la base
   Tupla3f c3(r / 2, 0.0f, r * sqrt(3) / 2);
   Tupla3f c4(-r / 2, 0.0f, r * sqrt(3) / 2);

   // Vértice de la cúspide
   Tupla3f c5(0.0f, h, 0.0f);

   // Inicializar tabla de vértices
   v = {c0, c1, c2, c3, c4, c5};

   // Inicializar tabla de caras
   Tupla3i ct0(4, 3, 5);
   Tupla3i ct1(2, 4, 5);
   Tupla3i ct2(0, 2, 5);
   Tupla3i ct3(1, 0, 5);
   Tupla3i ct4(1, 5, 3);

   Tupla3i ct5(4, 2, 0);
   Tupla3i ct6(4, 0, 3);
   Tupla3i ct7(3, 0, 1);

   f.resize(8);

   f = {ct0, ct1, ct2, ct3, ct4, ct5, ct6, ct7};

   // Inicializar tablas de colores
   c_p.resize(8);
   c_l.resize(8);
   c_s.resize(8);

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

   selection_color[0] = 255;
   selection_color[1] = 0;
   selection_color[2] = 255;
}