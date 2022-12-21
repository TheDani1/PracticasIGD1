// *****************************************************************************
//
// Clase textura (práctica 5)
//
// *****************************************************************************

// *****************************************************************************

#include "auxiliar.h"
#include "textura.h"

Textura::Textura(string archivo)
{

    // leer los texels de un archivo y
    // enviarlos a la GPU o la memoria de vídeo, inicializando el
    // identificador de textura de OpenGL

    jpg::Imagen *pimg = NULL;

    pimg = new jpg::Imagen(archivo);

    width = pimg->tamX();

    height = pimg->tamY();

    unsigned char *leidos;

    for (unsigned i = 0; i < height; i++)
    {
        for (unsigned j = 0; j < width; j++)
        {
            leidos = pimg->leerPixel(j, height - i - 1);
            // introducimos R
            data.push_back(*leidos);
            leidos++;

            // introducimos
            data.push_back(*leidos);
            leidos++;

            // introducimos B
            data.push_back(*leidos);
            leidos++;
        }
    }

    textura_id = -1;
}

void Textura::activar()
{

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // sin esta linea no funcionan
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (textura_id == -1)
    {
        glGenTextures(1, &textura_id);

        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, data.data());
    }

    glBindTexture(GL_TEXTURE_2D, textura_id);
}
