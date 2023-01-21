#include "camara.h"

// *****************************************************************************
//
// Clase camara (práctica 6)
//
// *****************************************************************************

// *****************************************************************************

void Camara::setObserver() { gluLookAt(eye(0), eye(1), eye(2),
									   at(0), at(1), at(2),
									   up(0), up(1), up(2)); }

Camara::Camara(const Tupla3f &eye, const Tupla3f &at, const Tupla3f &up,
			   const TipoCamara &tipo, const float near, const float far)
{

	this->eye = eye;
	this->at = at;
	this->up = up;

	this->tipo = tipo;

	this->near = near;
	this->far = far;
}

void Camara::girar(int x, int y)
{

	if ((at - eye)(2) > 0)
		y = -y;

	// at = {at(0) + x, at(1) - y, at(2)};
	rotarXFirstPerson(-y * (M_PI / 180));
	rotarYFirstPerson(-x * (M_PI / 180));
}

void Camara::girar_examinar(int x, int y)
{
	rotarXExaminar(y * (M_PI/180));
	rotarYExaminar(x * (M_PI/180));
}

void Camara::rotarXExaminar(float angle)
{
	Tupla3f eye_centro = eye - at;

	float modulo = sqrt(eye_centro.lengthSq());

	// eye(1) = cos(angulo)*eye(1) - sin(angulo) * eye(2);
	eye_centro(1) = cos(angle) * eye_centro(1) - sin(angle) * eye_centro(2);

	// eye(2) = sin(angulo) * eye(1) + cos(angulo) * eye(2);
	eye_centro(2) = sin(angle) * eye_centro(1) + cos(angle) * eye_centro(2);

	eye_centro = eye_centro.normalized() * modulo;

	eye = eye_centro + at;
}

void Camara::rotarYExaminar(float angle)
{
	Tupla3f eye_centro = eye - at;

	float modulo = sqrt(eye_centro.lengthSq());

	eye_centro(0) = cos(angle) * eye_centro(0) + sin(angle) * eye_centro(2);

	eye_centro(2) = -sin(angle) * eye_centro(0) + cos(angle) * eye_centro(2);

	eye_centro = eye_centro.normalized() * modulo;

	eye = eye_centro + at;
}

void Camara::rotarZExaminar(float angle)
{
	Tupla3f eye_centro = eye - at;

	float modulo = sqrt(eye_centro.lengthSq());

	eye_centro(0) = cos(angle) * eye_centro(0) - sin(angle) * eye_centro(1);

	eye_centro(1) = sin(angle) * eye_centro(0) + cos(angle) * eye_centro(1);

	eye_centro = eye_centro.normalized() * modulo;

	eye = eye_centro + at;
}

void Camara::rotarXFirstPerson(const float angulo)
{

	Tupla3f at_centro = at - eye;

	float modulo = sqrt(at_centro.lengthSq());

	at_centro(1) = cos(angulo) * at_centro(1) - sin(angulo) * at_centro(2);

	at_centro(2) = sin(angulo) * at_centro(1) + cos(angulo) * at_centro(2);

	at_centro = at_centro.normalized() * modulo;

	at = at_centro + eye;
}

void Camara::rotarYFirstPerson(const float angulo)
{

	Tupla3f at_centro = at - eye;

	float modulo = sqrt(at_centro.lengthSq());

	at_centro(0) = cos(angulo) * at_centro(0) + sin(angulo) * at_centro(2);

	at_centro(2) = -sin(angulo) * at_centro(0) + cos(angulo) * at_centro(2);

	at_centro = at_centro.normalized() * modulo;

	at = at_centro + eye;
}

void Camara::rotarZFirstPerson(const float angulo)
{

	Tupla3f at_centro = at - eye;

	float modulo = sqrt(at_centro.lengthSq());

	at_centro(0) = cos(angulo) * at_centro(0) - sin(angulo) * at_centro(1);

	at_centro(1) = sin(angulo) * at_centro(0) + cos(angulo) * at_centro(1);

	at_centro = at_centro.normalized() * modulo;

	at = at_centro + eye;
}

void Camara::mover(float x, float y, float z)
{
}

void Camara::zoom(float factor)
{
	aspect *= factor;
	fov *= factor;
	bottom *= factor;
	top *= factor;
}

void Camara::setAspect(const float &aspect)
{
	this->aspect = aspect;
}

void Camara::setFov(const float &fov)
{
	this->fov = fov;
}

void Camara::setNear(const float &near)
{
	this->near = near;
}

void Camara::setFar(const float &far)
{
	this->far = far;
}

void Camara::setBottom(const float &bottom)
{
	this->bottom = bottom;
}

void Camara::setTop(const float &top)
{
	this->top = top;
}

float Camara::getBottom()
{
	return bottom;
}

float Camara::getTop()
{
	return top;
}

void Camara::setProyeccion()
{
	// bien aspect, fov, near, far; // o bien left, right, near, far;
	if (tipo == PERSPECTIVA)
	{
		// std::cout << near << " ";
		glFrustum(aspect, fov, bottom, top, near, far);
	}
	else
	{
		glOrtho(aspect, fov, bottom, top, near, far);
	}
}

void Camara::setAt(const Tupla3f &at)
{
	this->at = at;
}

void Camara::setObjetoSeleccionado(const objetos &objeto)
{

	this->objeto_seleccionado = objeto;
}

objetos Camara::getObjetoSeleccionado()
{
	return this->objeto_seleccionado;
}
