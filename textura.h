
// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: textura.h (Práctica 5)
//
// #############################################################################

#ifndef TEXTURA_H_INCLUDED
#define TEXTURA_H_INCLUDED

#include "auxiliar.h"
#include "jpg_imagen.hpp"
#include <string>

using std::string;
class Textura
{

    private:
    
    GLuint textura_id = 0;
    std::vector<unsigned char> data;
    int width, height;

    public:

    Textura(string archivo) ;

    void activar();
};

#endif