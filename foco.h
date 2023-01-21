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

   void draw(const modoVisual modo);

   void addGiroY(float giroY);
   void addGiroZ(float giroZ);
   
   void addTransX(float transX);

   void setMaterial(const Material &mat);

   void setTextura(const std::string &archivo1, const std::string &archivo2, const std::string &archivo3);

   void setColorSeleccion(unsigned char selec[3]);


   float getGiroY();
   float getGiroZ();
   float getTransX();

   Tupla3f getCentro();

   private:
   Cilindro *cilindro = nullptr;
   Cubo *cubo=nullptr;
   ObjPLY *objply=nullptr;

   float giroY = 0; // GIRO INFINITO
   float giroZ = 0; // GIRO Z COMO MÁXIMO 95 Y COMO MÍNIMO -95

   float transX = 0;


};




#endif