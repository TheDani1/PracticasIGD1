#include "auxiliar.h"
#include "luz.h"
#include "luzDireccional.h"

// *****************************************************************************
//
// Clase luzDireccional (práctica 2)
//
// *****************************************************************************

// *****************************************************************************

LuzDireccional::LuzDireccional(const Tupla2f direccion,
                     const GLenum idLuzOpenGL,
                     const Tupla4f colorAmbiente,
                     const Tupla4f colorEspecular,
                     const Tupla4f colorDifuso){
    this->id = idLuzOpenGL;
    this->colorAmbiente = colorAmbiente;
    this->colorEspecular = colorEspecular;
    this->colorDifuso = colorDifuso;

    this->alpha = direccion(0);
    this->beta = direccion(1);

    // Pasamos de coordenadas esféricas a cartesianas
    this->posicion = {cosf(direccion(0))*sinf(direccion(1)), cosf(direccion(1)), sinf(direccion(0))*sinf(direccion(1)), 0.0f};
}