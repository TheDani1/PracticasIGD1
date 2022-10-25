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

class LuzDireccional : public Luz
{
public:
    LuzDireccional(const Tupla2f &orientacion);
};

#endif
