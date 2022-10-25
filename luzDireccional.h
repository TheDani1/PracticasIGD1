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
    LuzDireccional(const Tupla2f &orientacion);

    void variarAnguloAlpha(float incremento);
    void variarAnguloBeta(float incremento);
};

#endif
