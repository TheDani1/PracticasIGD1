#include "objply.h"
#include "ply_reader.h"
 

// *****************************************************************************
//
// Clase ObjPLY (práctica 2)
//
// *****************************************************************************

ObjPLY::ObjPLY( const std::string & nombre_archivo )
{
   // leer la lista de caras y vértices
   ply::read( nombre_archivo, this->v, this->f );

   c_p.resize(v.size());
   c_l.resize(v.size());
   c_s.resize(v.size());

   Tupla3f rojo  ( 1 , 0 , 0 );
   Tupla3f verde ( 0 , 1 , 0 );
   Tupla3f azul  ( 0 , 0 , 1 );

   color_puntos(rojo);

   color_lineas(verde);

   color_solido(azul);

}


