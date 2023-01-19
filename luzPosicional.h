// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: luzPosicional.h (Práctica 2)
//
// #############################################################################

#ifndef LUZPOSICIONAL_H_INCLUDED
#define LUZPOSICIONAL_H_INCLUDED

#include "luz.h"
#include "auxiliar.h"

class LuzPosicional : public Luz
{
public:
    LuzPosicional(const Tupla3f direccion,
                     const GLenum idLuzOpenGL,
                     const Tupla4f colorAmbiente = Tupla4f(0.0f, 0.0f, 0.0f, 1.0f),
                     const Tupla4f colorEspecular = Tupla4f(1.0f, 1.0f, 1.0f, 1.0f),
                     const Tupla4f colorDifuso = Tupla4f(1.0f, 1.0f, 1.0f, 1.0f));
};

#endif
