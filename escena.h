#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "piramidepentagonal.h"
#include "objply.h"
#include "objrevolucion.h"
#include "esfera.h"
#include "cono.h"
#include "cilindro.h"
#include "flecha.h"
#include "foco.h"
#include "cuadro.h"

#include "luz.h"
#include "luzDireccional.h"
#include "luzPosicional.h"

typedef enum
{
    NADA,
    SELOBJETO,
    SELVISUALIZACION,
    MOVIMIENTO,
    ANIMACION,
    LUZ
} menu;

class Escena
{

private:

    bool visual_obj[4] = {false , false, true, false}; // Puntos, lineas, solido, iluminación
    bool sel_obj[7] = {true, true, true, false, true, false, false}; // Piramide, cilindro, esfera, peón, cubo , escultura y foco (mj)
    bool grad_lib[3] = {false, false, false}; // Giro Y, Giro Z, Translate

    float velocidadAnimacionX = 1.0f; // LIMITE DE 17 y -17
    float velocidadAnimacionZY = 1.0f; // LIMITE DE 90 y -90

    float rotacionLuzPuntual = 0.0f;
    float velocidadLuzPuntual = 1.3f;

    float factor_aumento = 0.001F;

    bool animacion = false;
    bool animacion_luz = false;
    bool animacion_color = false;

    // ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)

    // variables que definen la posicion de la camara en coordenadas polares
    GLfloat Observer_distance;
    GLfloat Observer_angle_x;
    GLfloat Observer_angle_y;

    // variables que controlan la ventana y la transformacion de perspectiva
    GLfloat Width, Height, Front_plane, Back_plane;

    // Transformación de cámara
    void change_projection(const float ratio_xy);
    void change_observer();

    void clear_window();

    menu modoMenu = NADA;
    // Objetos de la escena
    Ejes ejes;
    Cubo *cubo = nullptr;                   // es importante inicializarlo a 'nullptr'
    // PiramidePentagonal *piramide = nullptr; // es importante inicializarlo a 'nullptr'
    ObjPLY *objply = nullptr;                  // es importante inicializarlo a 'nullptr'
    ObjRevolucion *objrevolucion = nullptr;    // es importante inicializarlo a 'nullptr'
    ObjRevolucion *objrevolucion1 = nullptr;    // es importante inicializarlo a 'nullptr'
    Esfera *esfera = nullptr;                  // es importante inicializarlo a 'nullptr'
    Cono *cono = nullptr;                      // es importante inicializarlo a 'nullptr'
    Cilindro *cilindro = nullptr;              // es importante inicializarlo a 'nullptr'
    Foco *foco = nullptr;                      // es importante inicializarlo a 'nullptr'
    Cuadro *cuadro = nullptr;                  // es importante inicializarlo a 'nullptr'

    // Flecha *flecha = nullptr;
    // Flecha *flecha1 = nullptr;
    // Flecha *flecha2 = nullptr;

    LuzPosicional *luz0 = nullptr;
    LuzDireccional *luz1 = nullptr;

    void visualizar_menu();
    void evento(string evento);
    void error(string error);

public:
    Escena();
    void inicializar(int UI_window_width, int UI_window_height);
    void redimensionar(int newWidth, int newHeight);

    // Dibujar
    void dibujar();

    // Interacción con la escena
    bool teclaPulsada(unsigned char Tecla1, int x, int y);
    void teclaEspecial(int Tecla1, int x, int y);

    void animarModeloJerarquico();
};
#endif
