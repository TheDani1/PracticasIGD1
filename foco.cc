// *****************************************************************************
//
// Clase foco (práctica 4)
//
// *****************************************************************************

// *****************************************************************************

#include "auxiliar.h"
#include "foco.h"

Foco::Foco()
{

    cilindro = new Cilindro(20, 20, 1, 1);
    objply = new ObjPLY("plys/base_foco2.ply");
    cubo = new Cubo(1);

    cubo->calcular_centro_cubo();
}

void Foco::draw(const modoVisual modo)
{

    glPushMatrix();

    glPushMatrix();
    glTranslatef(-20, -2.5, -2.5);
    glScalef(40, 5, 5);
    cubo->draw(modo);
    glPopMatrix();

    glRotatef(180, 0, 0, 1);

    glPushMatrix();

    glTranslatef(0, 2.5, 0);
    glTranslatef(transX, 0, 0);

    // BASE
    glPushMatrix();
    glScalef(2.5, 0.5, 2.5);
    cilindro->draw(modo);
    glPopMatrix();

    // CILINDRO PARA GIRAR
    glPushMatrix();
    glTranslatef(0, 0.5, 0);
    glScalef(0.5, 0.5, 0.5);
    cilindro->draw(modo);
    glPopMatrix();

    glPushMatrix();
    glRotatef(giroY, 0, 1, 0);
    // TODA LA ESTRUCTURA PRINCIPAL DEL FOCO
    glTranslatef(0, 1.5, 0);
    glPushMatrix();
    // AQUI ENTRAMOS EN EL FOCO EN SÍ
    glTranslatef(0, 4, 0);
    glPushMatrix();
    glPushMatrix();
    glRotatef(giroZ, 1, 0, 0);
    glTranslatef(0, -3.5, 0);
    glPushMatrix();
    glTranslatef(5.75, 3.5, 0);
    glRotatef(90, 0, 0, 1);
    glScalef(0.5, 11.5, 0.5);
    cilindro->draw(modo);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, 2, 0);
    glScalef(3.5, 7, 3.5);
    cilindro->draw(modo);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, -4, 0);
    glRotatef(90, 0, 1, 0);
    glScalef(2, 2.5, 2);
    objply->draw(modo);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
}

void Foco::addGiroY(float giroY)
{

    this->giroY += giroY;
}

void Foco::addGiroZ(float giroZ)
{

    this->giroZ += giroZ;
}

void Foco::addTransX(float transX)
{
    this->transX += transX;
}

float Foco::getGiroY()
{
    return giroY;
}

float Foco::getGiroZ()
{
    return giroZ;
}

float Foco::getTransX()
{
    return transX;
}

Tupla3f Foco::getCentro()
{
    return cubo->getCentro();
}

void Foco::setMaterial(const Material &mat)
{
    cilindro->setMaterial(mat);
    objply->setMaterial(mat);
    cubo->setMaterial(mat);
}

void Foco::setTextura(const std::string &archivo1, const std::string &archivo2, const std::string &archivo3)
{
    cilindro->setTextura(archivo1);
    objply->setTextura(archivo2);
    cubo->setTextura(archivo3);
}

void Foco::setColorSeleccion(unsigned char selec[3])
{
    cilindro->setColorSeleccion(selec);
    objply->setColorSeleccion(selec);
    cubo->setColorSeleccion(selec);
}
