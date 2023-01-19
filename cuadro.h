// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: cuadro.h (Práctica 2)
//
// #############################################################################

#ifndef CUADRO_H_INCLUDED
#define CUADRO_H_INCLUDED

#include "auxiliar.h"
#include "malla.h"

class Cuadro : public Malla3D
{
   public:
   Cuadro(const float lado=1.0F) ;

};

#endif