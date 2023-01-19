#include "auxiliar.h"
#include "luz.h"
#include "luzPosicional.h"

// *****************************************************************************
//
// Clase luzPosicional (práctica 2)
//
// *****************************************************************************

// *****************************************************************************

LuzPosicional::LuzPosicional(const Tupla3f direccion,
                     const GLenum idLuzOpenGL,
                     const Tupla4f colorAmbiente,
                     const Tupla4f colorEspecular,
                     const Tupla4f colorDifuso){

    this->id = idLuzOpenGL;
    this->colorAmbiente = colorAmbiente;
    this->colorEspecular = colorEspecular;
    this->colorDifuso = colorDifuso;

    this->posicion = {direccion(0), direccion(1), direccion(2), 1};
    
}