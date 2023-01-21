// *****************************************************************************
//
// Clase textura (práctica 5)
//
// *****************************************************************************

// *****************************************************************************

#include "auxiliar.h"
#include "textura.h"

Textura::Textura()
{

    // // leer los texels de un archivo y
    // // enviarlos a la GPU o la memoria de vídeo, inicializando el
    // // identificador de textura de OpenGL

    // jpg::Imagen *pimg = NULL;

    // pimg = new jpg::Imagen(archivo);

    // width = pimg->tamX();

    // height = pimg->tamY();

    // unsigned char *texels;

    // // Leer los valores de la imagen
    // for(unsigned i = 0 ; i < width ; i++)
    // {
    //     for(unsigned j = 0 ; j < height ; j++)
    //     {
    //         // Nos aseguramos de coger los valores desde la esquina superior izquierda
    //         texels = pimg->leerPixel(i, height - j - 1);
    //         // Al ser 3 valores (RGB) tenemos que introducir los 3 en data
    //         for(int k = 0 ; k < 3 ; k++)
    //         {
    //             data.push_back(*texels);
    //             texels++;
    //         }
    //     }
    // }
}

void Textura::crearTextura(const std::string &archivo)
{
    pimg = new jpg::Imagen(archivo);

    glGenTextures(1, &textura_id);
    glBindTexture(GL_TEXTURE_2D, textura_id);
}

void Textura::activar()
{

    if (pimg != NULL)
    {

        // Configurar cómo se debe repetir la textura
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // Configurar el filtro de escalado
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // // sin esta linea no funcionan

        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, pimg->tamX(), pimg->tamY(), GL_RGB, GL_UNSIGNED_BYTE, pimg->leerPixels());
    }

    // glEnable(GL_TEXTURE_2D);

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // // // sin esta linea no funcionan
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // if (textura_id == 0)
    // {
    //     std::cout << "Genero textura" << std::endl;
    //     glGenTextures(1, &textura_id);

    // 	glBindTexture(GL_TEXTURE_2D, textura_id);

    //     gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, data.data());
    // }

    // glBindTexture(GL_TEXTURE_2D, textura_id);
}

bool Textura::texturaActivada()
{
    return pimg != NULL;
}
