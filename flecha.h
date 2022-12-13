// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: flecha.h (Práctica examen)
//
// #############################################################################

#ifndef FLECHA_H_INCLUDED
#define FLECHA_H_INCLUDED

#include "auxiliar.h"
#include "malla.h"
#include "objrevolucion.h"

class Flecha : public ObjRevolucion
{
public:
    Flecha(float hPunta, float hAstil, int nRev);
};

#endif
