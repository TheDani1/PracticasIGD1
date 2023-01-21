#include "auxiliar.h"
#include "cuadro.h"

// *****************************************************************************
//
// Clase Cuadro (práctica 5)
//
// *****************************************************************************

// *****************************************************************************
// Cuadro generado a partir de dos triángulos para pruebas de la práctica 5

Cuadro::Cuadro(const float lado)
{
    // un cubo tiene 9 vertices
    v.resize(4);

    // y 6 caras, 12 trianguladas

    // inicializar la tabla de vértices
    Tupla3f v0(0.0f, 0.0f, 0.0f);
    Tupla3f v1(lado, 0.0f, 0.0f);
    Tupla3f v2(0.0f, lado, 0.0f);
    Tupla3f v3(lado, lado, 0.0f);

    v = {v0, v1, v2, v3};

    // inicializar la tabla de caras o triángulos:
    // (es importante en cada cara ordenar los vértices en sentido contrario
    //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

    f.resize(2);

    // cara trasera
    Tupla3i f0 (0, 1, 3); // par
    Tupla3i f1 (3, 2, 0); // impar

    f = {f0, f1};

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

    Tupla3u amarillo(255, 255, 0);

    
    //selection_color = amarillo;

    //modo_textura = PLANA;

	//textura = new Textura("textures/text-madera.jpg");

    ct.resize(v.size());

    Tupla2f ct0(0.0f, 0.0f);
    Tupla2f ct1(1.0f, 0.0f);
    Tupla2f ct2(0.0f, 1.0f);
    Tupla2f ct3(1.0f, 1.0f);

    ct = {ct0, ct1, ct2, ct3};

    calcularNormales();

    calcular_centro_malla();

    selection_colors = new unsigned char[128 * 3 * v.size()];

    selection_color[0] = 255;
    selection_color[1] = 0;
    selection_color[2] = 0;


}
