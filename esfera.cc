#include "auxiliar.h"
#include "esfera.h"

// *****************************************************************************
//
// Clase Cilindro (práctica 2)
//
// *****************************************************************************

// *****************************************************************************
// Esfera generada a partir de perfil de revolución desde constructor propio

Esfera::Esfera(const int num_vert_perfil, const int num_instancias_perf, const float radio)
{

    // Simplemente crear el perfil original y una vez creado
    // llamar a crearMalla

    // Crear el perfil original
    std::vector<Tupla3f> perfil_original;

    // Crear el perfil original
    // Crear perfil de una esfera
    for (int i = 1; i < num_vert_perfil - 1; i++)
    {
        float angulo = (i * M_PI) / (num_vert_perfil - 1);
        float x = radio * sin(angulo);
        float y = radio * cos(angulo);
        perfil_original.push_back(Tupla3f(x, y, 0));
    }

    perfil_original.push_back(Tupla3f(0, radio*-1, 0));
    perfil_original.push_back(Tupla3f(0, radio, 0));

    std::cout << "Esto se pasa a la función crearMalla" << std::endl;
    for(int i = 0; i < perfil_original.size(); i++){
        std::cout << perfil_original[i] << std::endl;
    }

    crearMalla(perfil_original, num_instancias_perf);

    c_p.resize(v.size());
    c_l.resize(v.size());
    c_s.resize(v.size());

    Tupla3f rojo(1, 0, 0);
    Tupla3f verde(0, 0, 0);
    Tupla3f azul(0, 0, 1);

    color_puntos(rojo);

    color_lineas(verde);

    color_solido(azul);
}