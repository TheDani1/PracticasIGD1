#include "auxiliar.h"
#include "objrevolucion.h"
#include <algorithm>

#define EPSILON 0.0001

// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion(const std::string &archivo) {

   ply::read_vertices(archivo, this->v);

   c_p.resize(v.size());
   c_l.resize(v.size());
   c_s.resize(v.size());

   Tupla3f rojo(1, 0, 0);
   Tupla3f verde(0, 1, 0);
   Tupla3f azul(0, 0, 1);

   Tupla3f blanco(0.9f, 0.9f, 0.9f);

   Tupla3f negro(0.0f, 0.0f, 0.0f);

   point_color = rojo;

   line_color = verde;

   solid_color = blanco;

   selection_colors = new unsigned char[128 * 3 * v.size()];

   selection_color[0] = 0;
   selection_color[1] = 255;
   selection_color[2] = 0;
}

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string &archivo, int num_instancias, const tipoTextura &modo, bool conTextura)
{
   // completar ......(práctica 2)

   // Simplemente crear el perfil original y una vez creado
   // llamar a crearMalla

   ply::read_vertices(archivo, this->v);

   this->tipotext = modo;

   crearMalla(v, num_instancias, tipotext);

   c_p.resize(v.size());
   c_l.resize(v.size());
   c_s.resize(v.size());

   Tupla3f rojo(1, 0, 0);
   Tupla3f verde(0, 1, 0);
   Tupla3f azul(0, 0, 1);

   Tupla3f blanco(0.9f, 0.9f, 0.9f);

   Tupla3f negro(0.0f, 0.0f, 0.0f);

   point_color = rojo;

   line_color = verde;

   solid_color = blanco;

   selection_colors = new unsigned char[128 * 3 * v.size()];

   selection_color[0] = 0;
   selection_color[1] = 255;
   selection_color[2] = 0;
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool conTextura)
{
}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, const tipoTextura &modo)
{

   // VERIFICAMOS QUE ESTÉ EN EL SENTIDO QUE NOSOTROS QUEREMOS Y SI NO LO INVERTIMOS

   std::vector<Tupla3f> perfil_inverso = perfil_original;

   bool inverso = false;

   for (int i = 0; i < perfil_original.size(); i++) // HE CAMBIADO ESTO A +1
   {

      if (perfil_original[i](1) < perfil_original[i + 1](1))
      {
         inverso = true;
      }
      else
      {
         inverso = false;
      }
   }

   if (inverso)
   {
      std::reverse(perfil_inverso.begin(), perfil_inverso.end());
   }

   // Se le asignan valores basura
   Tupla3f polo_sur = {-1, -1, -1};
   Tupla3f polo_norte = {-1, -1, -1};

   bool tapa_sup = false;
   bool tapa_inf = false;

   if (fabs(perfil_inverso.front()(X)) < EPSILON && perfil_inverso.front()(Z) < EPSILON)
   {

      polo_sur = perfil_inverso.front();
      perfil_inverso.erase(perfil_inverso.begin());

      tapa_inf = true;
   }

   if (fabs(perfil_inverso.back()(X)) < EPSILON && perfil_inverso.back()(Z) < EPSILON)
   {

      polo_norte = perfil_inverso.back();
      perfil_inverso.pop_back();

      tapa_sup = true;
   }

   v.clear();

   // GENERAMOS PERFIL (VERTICES)
   for (int j = 0; j < num_instancias; j++)
   {

      float angulo = (2 * M_PI / num_instancias) * j;

      for (int k = 0; k < perfil_inverso.size(); k++)
      {

         float x = perfil_inverso[k](X) * cos(angulo) + perfil_inverso[k](Z) * sin(angulo);
         float z = perfil_inverso[k](X) * -sin(angulo) + perfil_inverso[k](Z) * cos(angulo);
         float y = perfil_inverso[k](Y);

         Tupla3f perfil_n(x, y, z);

         v.push_back(perfil_n);
      }
   }

   // GENERAMOS CARAS

   f.clear();

   // desde 0 hasta el numero de instancias - 1
   for (int i = 0; i < num_instancias; i++)
   {
      // desde 0 hasta el numero de vertices originales - 2
      for (int j = 0; j < perfil_inverso.size() - 1; j++)
      {
         int a = perfil_inverso.size() * i + j;
         int b = perfil_inverso.size() * ((i + 1) % num_instancias) + j;

         Tupla3i cara1(a, b, b + 1);
         Tupla3i cara2(a, b + 1, a + 1);

         f.push_back(cara1);
         f.push_back(cara2);
      }
   }

   perfil_original = perfil_inverso;

   if (tapa_sup && !tapa_inf)
   {

      v.push_back(polo_sur);
      tapaSuperior(perfil_original, num_instancias, v.size() - 1);
   }
   else if (tapa_inf && !tapa_sup)
   {

      v.push_back(polo_norte);
      tapaInferior(perfil_original, num_instancias, v.size() - 1);
   }
   else if (tapa_inf && tapa_sup)
   {

      v.push_back(polo_sur);
      v.push_back(polo_norte);

      tapaSuperior(perfil_original, num_instancias, v.size() - 1);
      tapaInferior(perfil_original, num_instancias, v.size() - 2);
   }

   calcularNormales();

}

void ObjRevolucion::tapaSuperior(std::vector<Tupla3f> perfil_original, int num_instancias, int norte)
{

   int pos_aux1;
   int pos_aux2;

   // Generamos caras del polo superior

   for (int i = 0; i < num_instancias - 1; i++)
   {

      pos_aux1 = perfil_original.size() * (i + 1) - 1;

      pos_aux2 = pos_aux1 + perfil_original.size();

      f.push_back(Tupla3i(pos_aux2, norte, pos_aux1));
   }

   pos_aux1 = perfil_original.size() * num_instancias - 1;

   // primer vertice
   pos_aux2 = perfil_original.size() - 1;

   f.push_back(Tupla3i(pos_aux2, norte, pos_aux1));
}

void ObjRevolucion::tapaInferior(std::vector<Tupla3f> perfil_original, int num_instancias, int sur)
{

   int pos_aux1 = 0;
   int pos_aux2 = 0;

   // Generamos caras del polo inferior

   for (int i = 0; i < num_instancias - 1; i++)
   {

      pos_aux1 = perfil_original.size() * i;

      pos_aux2 = pos_aux1 + perfil_original.size();

      f.push_back(Tupla3i(pos_aux1, sur, pos_aux2));
   }

   // Union de la ultima cara con la primera

   f.push_back(Tupla3i(perfil_original.size() * (num_instancias - 1), sur, 0));
}

void ObjRevolucion::calcularCoordTextura(const tipoTextura &modo, std::vector<Tupla3f> perfil_original, int num_instancias)
{

   ct.resize(v.size());

   float alpha, beta, h;

   float s, t;

   switch (modo)
   {
   case CILINDRICA:{
      for (int i = 0; i < ct.size(); i++)
      {
         alpha = atan2(v[i](2), v[i](0));
         h = v[i](1);

         s = 1 - (0.5 + (alpha / (M_PI * 2)));
         s += 0.5;
         s = fmod(s, 1.0);

         // std::cout << s <<  " " << alpha << std::endl;
         t = (h - perfil_original.front()(1)) / (perfil_original.back()(1) - perfil_original.front()(1));

         ct[i] = {s, t};
      }

      break;
   }

   case ESFERICA:{
      for (int i = 0; i < ct.size(); i++)
      {
         alpha = atan2(v[i](2), v[i](0));
         beta = atan2(v[i](1), sqrt(pow(v[i](0), 2) + pow(v[i](2), 2)));

         s = 1 - (0.5 + (alpha / (M_PI * 2)));
         s += 0.5;
         s = fmod(s, 1.0);
         t = 0.5 + beta / M_PI;

         ct[i] = {s, t};
      }

      break;
   }
   case PLANA:
      for (int i = 0; i < ct.size(); i++)
      {
         ct[i] = {v[i](0), (v[i](1) - v.front()(1)) / (v.back()(1) - v.front()(1))};
      }
      break;
   }
}