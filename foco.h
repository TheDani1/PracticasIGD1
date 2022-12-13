// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: foco.h (Práctica 4)
//
// #############################################################################

#ifndef FOCO_H_INCLUDED
#define FOCO_H_INCLUDED

#include "auxiliar.h"
#include "malla.h"
#include "objrevolucion.h"
#include "objply.h"
#include "cilindro.h"
#include "cubo.h"

// *****************************************************************************
//
// Clase Modelo Jerarquico
//
// *****************************************************************************

// *****************************************************************************
// Modelo jerárquico que define un foco de luz de una discoteca o festival

class Foco
{
   public:
   Foco();

   void draw(const GLenum modo);

   void addGiroY(float giroY);
   void addGiroZ(float giroZ);
   
   void addTransX(float transX);

   float getGiroY();
   float getGiroZ();
   float getTransX();

   private:
   Cilindro *cilindro = nullptr;
   Cubo *cubo=nullptr;
   ObjPLY *objply=nullptr;

   float giroY = 0; // GIRO INFINITO
   float giroZ = 0; // GIRO Z COMO MÁXIMO 95 Y COMO MÍNIMO -95

   float transX = 0;

};




#endif