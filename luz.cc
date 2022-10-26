#include "auxiliar.h"
#include "luz.h"

// *****************************************************************************
//
// Clase Luz (práctica 2)
//
// *****************************************************************************

// *****************************************************************************


void Luz::activar() const{
    glLightfv(id, GL_AMBIENT, colorAmbiente);
    glLightfv(id, GL_DIFFUSE, colorDifuso);
    glLightfv(id, GL_SPECULAR, colorEspecular);
    glLightfv(id, GL_POSITION, posicion);
}