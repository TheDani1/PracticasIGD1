// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo:esfera.h (Práctica 2)
//
// #############################################################################

#ifndef ESFERA_H_INCLUDED
#define ESFERA_H_INCLUDED

#include "auxiliar.h"
#include "malla.h"
#include "objrevolucion.h"

class Esfera : public ObjRevolucion{

    public:

    Esfera( const int num_vert_perfil,
            const int num_instancias_perf,
            const float radio);

};

#endif