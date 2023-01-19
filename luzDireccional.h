// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: luzDireccional.h (Práctica 2)
//
// #############################################################################

#ifndef LUZDIRECCIONAL_H_INCLUDED
#define LUZDIRECCIONAL_H_INCLUDED

#include "luz.h"
#include "auxiliar.h"

class LuzDireccional : public Luz
{
protected:
    float alpha;
    float beta;

public:
    LuzDireccional(const Tupla2f direccion,
                     const GLenum idLuzOpenGL,
                     const Tupla4f colorAmbiente = Tupla4f(0.0f, 0.0f, 0.0f, 1.0f),
                     const Tupla4f colorEspecular = Tupla4f(1.0f, 1.0f, 1.0f, 1.0f),
                     const Tupla4f colorDifuso = Tupla4f(1.0f, 1.0f, 1.0f, 1.0f));

    void variarColorDifuso(float incremento);
};

#endif
