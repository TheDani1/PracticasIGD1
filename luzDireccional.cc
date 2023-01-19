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

void LuzDireccional::variarColorDifuso(float incremento){

    colorEspecular(0) += incremento*((rand() % 10)) ;
    colorEspecular(0) = fmod(colorEspecular(0), 1.0f);

    colorDifuso(0) += incremento*((rand() % 10)) ;
    colorDifuso(0) = fmod(colorDifuso(0), 1.0f);

    colorAmbiente(0) += incremento*((rand() % 10)) ;
    colorAmbiente(0) = fmod(colorAmbiente(0), 1.0f);

    colorEspecular(1) += incremento*((rand() % 10)) ;
    colorEspecular(1) = fmod(colorEspecular(1), 1.0f);

    colorDifuso(1) += incremento*((rand() % 10)) ;
    colorDifuso(1) = fmod(colorDifuso(1), 1.0f);

    colorAmbiente(1) += incremento*((rand() % 10)) ;
    colorAmbiente(1) = fmod(colorAmbiente(1), 1.0f);

    colorEspecular(2) += incremento*((rand() % 10)) ;
    colorEspecular(2) = fmod(colorEspecular(2), 1.0f);

    colorDifuso(2) += incremento*((rand() % 10)) ;
    colorDifuso(2) = fmod(colorDifuso(2), 1.0f);

    colorAmbiente(2) += incremento*((rand() % 10)) ;
    colorAmbiente(2) = fmod(colorAmbiente(2), 1.0f);

    colorEspecular(3) += incremento*((rand() % 10)) ;
    colorEspecular(3) = fmod(colorEspecular(3), 1.0f);

    colorDifuso(3) += incremento*((rand() % 10)) ;
    colorDifuso(3) = fmod(colorDifuso(3), 1.0f);

    colorAmbiente(3) += incremento*((rand() % 10)) ;
    colorAmbiente(3) = fmod(colorAmbiente(3), 1.0f);

}