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

    jpg ::Imagen *pimg = NULL;

    pimg = new jpg ::Imagen(archivo);

    tamx = pimg->tamX();
    // núm. columnas (unsigned)

    tamy = pimg->tamY();
    // núm. filas (unsigned|)
    
    texels = pimg->leerPixels(); // puntero texels (unsigned char *)
}

Textura::activar()
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
