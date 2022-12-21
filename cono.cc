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

    const float sep_h = radio / num_vert_perfil;
    const float sep_v = altura / num_vert_perfil;

    // Crear vértice de la punta
    perfil_original.push_back(Tupla3f(0, 0, 0));

    for (int i = 0; i <= num_vert_perfil; i++)
    {
        perfil_original.push_back({sep_h * (num_vert_perfil - i), sep_v * i, 0});
    }

    tipotext = CILINDRICA;

    crearMalla(perfil_original, num_instancias_perf, tipotext);

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