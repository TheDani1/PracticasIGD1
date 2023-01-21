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
#include "camara.h"

#include "luz.h"
#include "luzDireccional.h"
#include "luzPosicional.h"

#include <vector>
#include <utility>

#define MOUSE_WHEEL_UP 3
#define MOUSE_WHEEL_DOWN 4

typedef enum
{
    NADA,
    SELOBJETO,
    SELVISUALIZACION,
    MOVIMIENTO,
    ANIMACION,
    CAMARAS,
    LUZ
} menu;

typedef enum
{

    MOVIENDO_CAMARA_FIRSTPERSON,
    MOVIENDO_CAMARA_EXAMINAR,
    NONE

} EstadosRaton;

class Escena
{

private:
    bool visual_obj[4] = {false, false, true, false};              // Puntos, lineas, solido, iluminación
    bool sel_obj[8] = {true, true, true, true, true, true, true, true}; // Cubo, escultura, peón , esfera, cilindro, foco (mj), columna,  lampara y (Cuadro siempre aparece)   
    bool grad_lib[3] = {false, false, false};                      // Giro Y, Giro Z, Translate

    // Práctica 6 | Cámaras

    std::vector<Camara> camaras;
    int camaraActiva; // 0, 1, 2
    EstadosRaton estadoRaton = NONE;

    Tupla3f centroCamara(const Tupla3f &centro);

    bool invertMatrix(const float m[16], float invOut[16]);

    Material perla_emisiva;
    Material oro;
    Material turquesa;
    Material perla;
    Material plata;
    Material esmeralda;
    Material peon_blanco;
    Material peon_negro;
    Material obsidian;

    int xant = 0;
    int yant = 0;

    void dibujaSeleccion();

    void processPick(int x, int y);

    float velocidadAnimacionX = 1.0f;  // LIMITE DE 17 y -17
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
    void change_projection();
    void change_observer();

    GLfloat mat[16];

    void clear_window();

    menu modoMenu = NADA;
    // Objetos de la escena
    Ejes ejes;
    Cubo *cubo = nullptr; // es importante inicializarlo a 'nullptr'
    // PiramidePentagonal *piramide = nullptr; // es importante inicializarlo a 'nullptr'
    ObjPLY *escultura = nullptr;                // es importante inicializarlo a 'nullptr'
    ObjPLY *columna = nullptr;
    ObjRevolucion *peon = nullptr;  // es importante inicializarlo a 'nullptr'
    Esfera *esfera = nullptr;                // es importante inicializarlo a 'nullptr'
    Cono *cono = nullptr;                    // es importante inicializarlo a 'nullptr'
    Cilindro *cilindro = nullptr;            // es importante inicializarlo a 'nullptr'
    Foco *foco = nullptr;                    // es importante inicializarlo a 'nullptr'
    Cuadro *cuadro = nullptr;                // es importante inicializarlo a 'nullptr'

    ObjPLY *lampara = nullptr;
    Esfera *cielo = nullptr;

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

    void clickRaton(int boton, int estado, int x, int y);
    void ratonMovido(int x, int y);
};
#endif
