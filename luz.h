// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: luz.h (Práctica 2)
//
// #############################################################################

#ifndef LUZ_H_INCLUDED
#define LUZ_H_INCLUDED

#include "auxiliar.h"

class Luz
{

protected:
    Tupla4f posicion;
    GLenum id;
    Tupla4f colorAmbiente;
    Tupla4f colorDifuso;
    Tupla4f colorEspecular;

    bool active;

public:
    void activar() const;

    Luz();

    bool isActive() const;

    void activate();
};

#endif