#include "auxiliar.h"
#include "objrevolucion.h"
#include <algorithm>

// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string &archivo, int num_instancias)
{
   // completar ......(práctica 2)

   // Simplemente crear el perfil original y una vez creado
   // llamar a crearMalla

   ply::read_vertices(archivo, this->v);

   crearMalla(v, num_instancias);

   c_p.resize(v.size());
   c_l.resize(v.size());
   c_s.resize(v.size());

   Tupla3f rojo(1, 0, 0);
   Tupla3f verde(0, 1, 0);
   Tupla3f azul(0, 0, 1);

   color_puntos(rojo);

   color_lineas(verde);

   color_solido(azul);
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias)
{
}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias)
{

   // VERIFICAMOS QUE ESTÉ EN EL SENTIDO QUE NOSOTROS QUEREMOS Y SI NO LO INVERTIMOS

   std::cout << "Inverso?? " << perfil_original[0](1) << "<" << perfil_original[perfil_original.size() - 1](1) << std::endl;

   if (perfil_original[0](1) < perfil_original[perfil_original.size() - 1](1))
   {
      std::cout << "Orden invertido" << std::endl;
      std::reverse(perfil_original.begin(), perfil_original.end());
   }

   // Verificar si tenemos polos (eliminamos todos los puntos del eje Y que sean 0 y solo nos quedamos con los más grandes)

   float y_max = -INFINITY; // Y máxima para posteriormente calcular la altura max (si es más alto (o igual) es polo norte y si es mas bajo, polo sur)
   float y_min = +INFINITY;

   for (int i = 0; i < perfil_original.size(); i++)
   {

      if (perfil_original[i](Y) > y_max)
         y_max = perfil_original[i](Y);

      if (perfil_original[i](Y) < y_min)
         y_min = perfil_original[i](Y);
   }

   std::cout << y_max << " " << y_min << std::endl;

   // Una vez calculado el maximo y el mínimo
   // (que es donde están los polos podemos identificar los polos y solo dejar en el vector los polos reales (con y max y min))

   std::vector<Tupla3f> perfil_sin_polos;

   for (auto it = perfil_original.begin(); it < perfil_original.end(); ++it)
   {

      std::cout << (*it) << std::endl;

      if ((*it)(X) == 0 && (*it)(Z) == 0)
      {

         std::cout << "Polo encontrado " << std::endl;
         polos.push_back(*it);
         //perfil_original.erase(it);

      }else
      {
         perfil_sin_polos.push_back(*it);
      }
   }

   perfil_original.clear();
   perfil_original = perfil_sin_polos;

   v.clear();

   // GENERAMOS PERFIL (VERTICES)
   for (int j = 0; j < num_instancias; j++)
   {

      float angulo = (2 * M_PI / num_instancias) * j;

      for (int k = 0; k < perfil_original.size(); k++)
      {

         float x = perfil_original[k](X) * cos(angulo) + perfil_original[k](Z) * sin(angulo);
         float y = perfil_original[k](Y);
         float z = perfil_original[k](X) * -sin(angulo) + perfil_original[k](Z) * cos(angulo);

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
      for (int j = 0; j < perfil_original.size() - 1; j++)
      {
         int a = perfil_original.size() * i + j;
         int b = perfil_original.size() * ((i + 1) % num_instancias) + j;

         Tupla3i cara1(a, b, b + 1);
         Tupla3i cara2(a, b + 1, a + 1);

         f.push_back(cara1);
         f.push_back(cara2);
      }
   }

   // GENERAMOS CARAS DE LOS POLOS

   if (polos.size() > 0)
   {

      // Generamos caras de los polos a partir de los polos en el vector polos

      int pos_polo_norte = -1;
      int pos_polo_sur = -1;

      if (polos.size() > 1)
      {
         // Puede haber 2 o más polos (si hay 2 o más polos, el polo norte es el que tiene el Y más alto y el polo sur el que tiene el Y más bajo)

         std::cout << "Hay más de un polo" << std::endl;
         std::cout << polos.size() << std::endl;

         for (int i = 0; i < polos.size(); i++)
         {
            if (polos[i](Y) == y_max)
            {
               pos_polo_norte = i;
            }
            else if (polos[i](Y) == y_min)
            {
               pos_polo_sur = i;
            }
         }
         std::cout << "[N] Polo a meter: " << polos[pos_polo_norte] << std::endl;
         std::cout << "[S] Polo a meter: " << polos[pos_polo_sur] << std::endl;

         v.push_back(polos[pos_polo_norte]);
         v.push_back(polos[pos_polo_sur]);

         // El ultimo es el polo sur
         // El antepenultimo es el polo norte

         pos_polo_norte = v.size() - 2;
         pos_polo_sur = v.size() - 1;

         for(int i = 0; i < v.size(); i++){
            std::cout << "V[" << i << "] = " << v[i] << std::endl;
         }

         std::cout << "[N] Polo metidos: " << v[pos_polo_norte] << std::endl;
         std::cout << "[S] Polo metidos: " << v[pos_polo_sur] << std::endl;

         // Ahora solo deberían de quedar dos polos

         /*if (polos[pos_polo_sur](Y) > polos[pos_polo_norte](Y))
         {
            std::cout << polos[0] << " > " << polos[1] << std::endl;
            // El polo norte es el primero
            pos_polo_norte = v.size() - 2;
            pos_polo_sur = v.size() - 1;
         }
         else
         {
            std::cout << polos[0] << " < " << polos[1] << std::endl;
            // El polo norte es el segundo
            pos_polo_norte = v.size() - 2;
            pos_polo_sur = v.size() - 1;
         }*/

         std::cout << "Posicion polo norte: " << pos_polo_norte << std::endl;
         std::cout << "Posicion polo sur: " << pos_polo_sur << std::endl;

         // Generamos ambas tapas

         tapaSuperior(perfil_original, num_instancias, pos_polo_norte);
         tapaInferior(perfil_original, num_instancias, pos_polo_sur);
      }
      else
      { // Si nada más que hay un polo tenemos que ver si es superior o inferior y dibujar la tapa

         if (polos[0](Y) >= y_max)
         { // Si es mas alto o igual que la altura máxima es un polo norte.

            pos_polo_norte = v.size() - 1;

            tapaSuperior(perfil_original, num_instancias, pos_polo_norte);
         }
         else
         {
            pos_polo_sur = v.size() - 1;

            tapaInferior(perfil_original, num_instancias, pos_polo_sur);
         }
      }
   }
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

      f.push_back(Tupla3i(pos_aux1, norte, pos_aux2));
   }
}

void ObjRevolucion::tapaInferior(std::vector<Tupla3f> perfil_original, int num_instancias, int sur)
{

   int pos_aux1;
   int pos_aux2;

   // Generamos caras del polo inferior

   for (int i = 0; i < num_instancias - 1; i++)
   {

      pos_aux1 = perfil_original.size() * i;

      pos_aux2 = (pos_aux1 + perfil_original.size()) % sur;

      f.push_back(Tupla3i(pos_aux1, sur, pos_aux2));
   }
}