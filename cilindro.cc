#include "auxiliar.h"
#include "cilindro.h"

// *****************************************************************************
//
// Clase Cilindro (práctica 2)
//
// *****************************************************************************

// *****************************************************************************
// Cilindro generado a partir de perfil de revolución desde constructor propio

Cilindro::Cilindro(const int num_vert_perfil,
                   const int num_instancias_perf,
                   const float altura,
                   const float radio)
{

    tipotext = CILINDRICA;

    std::vector<Tupla3f> perfil_original;

    const float d_perf = altura / num_vert_perfil;

    perfil_original.push_back(Tupla3f(0, 0, 0));

    for (int i = 0; i < num_vert_perfil+1; i++)
    {
        perfil_original.push_back(Tupla3f(radio, i*d_perf, 0));
    }

    perfil_original.push_back(Tupla3f(0, altura, 0));

    tipotext = CILINDRICA;
    coordenadas_textura_creadas = true;

    crearMalla(perfil_original, num_instancias_perf, tipotext);

    //calcularCoordTextura(tipotext, perfil_original, num_instancias_perf);
    
    c_p.resize(v.size());
    c_l.resize(v.size());
    c_s.resize(v.size());

    Tupla3f rojo(1, 0, 0);
    Tupla3f verde(0, 1, 0);
    Tupla3f azul(0, 0, 1);
    Tupla3f blanco(0.9f, 0.9f, 0.9f);

    color_puntos(rojo);

    color_lineas(azul);

    color_solido(blanco);

    calcularCoordTextura(tipotext, perfil_original, num_instancias_perf);
}