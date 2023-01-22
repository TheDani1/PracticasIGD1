// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: camara.h (Práctica 6)
//
// #############################################################################

#ifndef CAMARA_H_INCLUDED
#define CAMARA_H_INCLUDED

#include "auxiliar.h"

typedef enum {ORTOGONAL, PERSPECTIVA} TipoCamara;

typedef enum
{
    CONO,
    ESCULTURA,
    PEON,
    ESFERA,
    CILINDRO,    
    FOCO,
    COLUMNA,
    LAMPARA,
    NINGUNO

} objetos;


class Camara
{

private:

    Tupla3f eye;
    Tupla3f at;
    Tupla3f up;

    int tipo;                     // ORTOGONAL o Perspectiva
    float aspect, fov, near, far; // o bien aspect, fov, near, far; // o bien left, right, near, far;

    float bottom, top;

    objetos objeto_seleccionado = NINGUNO;
    
public:

    Camara(const Tupla3f & eye, const Tupla3f & at, const Tupla3f & up,\
				   const TipoCamara & tipo, const float near, const float far);                  // con los parametros necesarios

    void girar(int x, int y);
    void girar_examinar(int x, int y);
    
    void rotarXExaminar(float angle);
    void rotarYExaminar(float angle);
    void rotarZExaminar(float angle);

    void rotarXFirstPerson(float angle);
    void rotarYFirstPerson(float angle);
    void rotarZFirstPerson(float angle);

    void zoom(float factor);

    void setAspect(const float & aspect);
    void setFov(const float & fov);
    void setNear(const float & near);
    void setFar(const float & far);
    void setBottom(const float & bottom);
    void setTop(const float & top);

    float getBottom();
    float getTop();

    void setObserver(); // completar
    void setProyeccion();
    void setAt(const Tupla3f & at);
    void setObjetoSeleccionado(const objetos & objeto);
    objetos getObjetoSeleccionado();
};

#endif