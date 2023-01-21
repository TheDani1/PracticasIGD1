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

    perfil_original.push_back(Tupla3f(0, radio, 0));
    // Crear el perfil original
    // Crear perfil de una esfera

    for (int i = 1; i < num_vert_perfil - 1; i++)
    {
        float angulo = (i * M_PI) / (num_vert_perfil - 1);
        float x = radio * sin(angulo);
        float y = radio * cos(angulo);
        perfil_original.push_back(Tupla3f(x, y, 0));
    }
    perfil_original.push_back(Tupla3f(0, radio * -1, 0));

    tipotext = ESFERICA;

    crearMalla(perfil_original, num_instancias_perf, tipotext);

    calcular_centro_malla();

    std::cout << "Tamano de perfil: " << perfil_original.size() << std::endl;
    std::cout << "Tamano de vertices: " << v.size() << std::endl;

    c_p.resize(v.size());
    c_l.resize(v.size());
    c_s.resize(v.size());

    Tupla3f rojo(1, 0, 0);
    Tupla3f verde(0, 1, 0);
    Tupla3f azul(0, 0, 1);
    Tupla3f blanco(0.9f, 0.9f, 0.9f);

    point_color = rojo;

    line_color = azul;

    solid_color = blanco;

    selection_colors = new unsigned char[128 * 3 * v.size()];

    selection_color[0] = 0;
    selection_color[1] = 255;
    selection_color[2] = 255;

    // color_puntos(rojo);

    // color_lineas(azul);

    // color_solido(blanco);

    tipotext = ESFERICA;
    coordenadas_textura_creadas = false;

    //calcularCoordTextura(tipotext, perfil_original, num_instancias_perf);

}