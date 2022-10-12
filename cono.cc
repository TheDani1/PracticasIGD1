#include "auxiliar.h"
#include "cono.h"

// *****************************************************************************
//
// Clase Cono (práctica 2)
//
// *****************************************************************************

// *****************************************************************************
// Cono generado a partir de perfil de revolución desde constructor propio

Cono::Cono(const int num_vert_perfil,
           const int num_instancias_perf,
           const float altura,
           const float radio)
{
    std::vector<Tupla3f> perfil_original;

    const float separacion_horizontal = radio / num_vert_perfil;
    const float separacion_vertical = altura / num_vert_perfil;

    for (int i = 0; i <= num_vert_perfil; i++)
    {
        perfil_original.push_back({separacion_horizontal * (num_vert_perfil - i), separacion_vertical * i, 0});
    }

    perfil_original.push_back(Tupla3f(0, 0, 0));

    crearMalla(perfil_original, num_instancias_perf);

    c_p.resize(v.size());
    c_l.resize(v.size());
    c_s.resize(v.size());

    Tupla3f rojo(1, 0, 0);
    Tupla3f verde(0, 1, 0);
    Tupla3f azul(0, 0, 1);

    color_puntos(rojo);

    color_lineas(azul);

    color_solido(verde);
}