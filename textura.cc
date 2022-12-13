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

    data.resize(3 * width * height);

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            unsigned char r, g, b;

            pimg->leerPixel(i, j);

            data[3 * (i + j * width)] = r;
            data[3 * (i + j * width) + 1] = g;
            data[3 * (i + j * width) + 2] = b;
        }
    }

    delete pimg;

    textura_id = -1;

    activar();
}

void Textura::activar()
{

    glEnable(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // sin esta linea no funcionan
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    if (textura_id == -1)
    {
        glGenTextures(1, &textura_id);
        glBindTexture(GL_TEXTURE_2D, textura_id);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data.data());
    }

    glBindTexture(GL_TEXTURE_2D, textura_id);
}
