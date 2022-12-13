#include "auxiliar.h"
#include "flecha.h"

Flecha::Flecha(float hPunta=1.0f, float hAstil=1.0f, int nRev=30){

    std::vector<Tupla3f> perfil_original;

    const float d_perf = hAstil / nRev;

    perfil_original.push_back(Tupla3f(0, 0, 0));

    for (int i = 0; i < nRev; i++)
    {

        perfil_original.push_back(Tupla3f(1, i*d_perf, 0));
    }

    perfil_original.push_back(Tupla3f(0, hAstil, 0));

    crearMalla(perfil_original, nRev);

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