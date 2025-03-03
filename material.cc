#include "material.h"

Material::Material(Tupla4f mdifuso,
                   Tupla4f mespecular,
                   Tupla4f mambiente,
                   float brillo)
{
    this->difuso = mdifuso;
    this->especular = mespecular;
    this->ambiente = mambiente;
    this->brillo = brillo;
    this->emision = {0.0f, 0.0f, 0.0f, 1.0f};
}

void Material::setEmision(Tupla4f emision)
{
    this->emision = emision;
}

Material::Material()
{
    this->difuso = {0.8f, 0.8f, 0.8f, 1.0f};
    this->especular = {0.0f, 0.0f, 0.0f, 1.0f};
    this->ambiente = {0.2f, 0.2f, 0.2f, 1.0f};
    this->brillo = 0;
    this->emision = {0.0f, 0.0f, 0.0f, 1.0f};
}

void Material::aplicar()
{

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, this->ambiente);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, this->difuso);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, this->especular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this->brillo);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, this->emision);

    glColorMaterial(GL_FRONT_AND_BACK, GL_EMISSION);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);
    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
    glColorMaterial(GL_FRONT_AND_BACK, GL_SPECULAR);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}

// glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiente);
// glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, difuso);
// glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, especular);
// glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brillo);

// glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);
// glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
// glColorMaterial(GL_FRONT_AND_BACK, GL_SPECULAR);
// glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
