// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo:material.h (Práctica 2)
//
// #############################################################################

#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include "auxiliar.h"

class Material{

private:
    Tupla4f difuso;
    Tupla4f especular;
    Tupla4f ambiente;

    float brillo;

public:

    Material();

    Material(Tupla4f mdifuso,
             Tupla4f mespecular,
             Tupla4f mambiente,
             float brillo);

    void aplicar();

};

#endif