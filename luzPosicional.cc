#include "auxiliar.h"
#include "luz.h"
#include "luzPosicional.h"

// *****************************************************************************
//
// Clase luzPosicional (práctica 2)
//
// *****************************************************************************

// *****************************************************************************

LuzPosicional::LuzPosicional(const Tupla2f direccion,
                     const GLenum idLuzOpenGL,
                     const Tupla4f colorAmbiente,
                     const Tupla4f colorEspecular,
                     const Tupla4f colorDifuso){

    this->id = idLuzOpenGL;
    this->colorAmbiente = colorAmbiente;
    this->colorEspecular = colorEspecular;
    this->colorDifuso = colorDifuso;

    this->posicion = {posicion[0], posicion[1], 0.0f, 1.0f};
    
}