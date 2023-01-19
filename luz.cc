#include "auxiliar.h"
#include "luz.h"

// *****************************************************************************
//
// Clase Luz (práctica 2)
//
// *****************************************************************************

// *****************************************************************************


void Luz::activar() const{

    if(active){
        glLightfv(id, GL_AMBIENT, colorAmbiente);
        glLightfv(id, GL_DIFFUSE, colorDifuso);
        glLightfv(id, GL_SPECULAR, colorEspecular);
        glLightfv(id, GL_POSITION, posicion);
    }
}

Luz::Luz(){
    active = false;
}

bool Luz::isActive() const{
    return active;
}

void Luz::activate(){

    active = !active;

    if(active){
        glEnable(id);
    }else{
        glDisable(id);
    }
}