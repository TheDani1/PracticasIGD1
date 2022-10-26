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

   color_lineas(azul);

   color_solido(verde);
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias)
{
}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias)
{

   // VERIFICAMOS QUE ESTÉ EN EL SENTIDO QUE NOSOTROS QUEREMOS Y SI NO LO INVERTIMOS

   bool inverso = false;

   for(int i = 0; i < perfil_original.size()-1; i++){
      
      if(perfil_original[i](1) < perfil_original[i+1](1)){
         inverso = true;
      }else{
         inverso=false;
      }
   }

   if (inverso)
   {
      std::reverse(perfil_original.begin(), perfil_original.end());
   }

   std::vector<Tupla3f> perfil_sin_polos;

   for (auto it = perfil_original.begin(); it < perfil_original.end(); ++it)
   {

      

      if ((*it)(X) == 0 && (*it)(Z) == 0 && (it == perfil_original.end() - 1 || it == perfil_original.begin()))
      {

         //std::cout << "Polo encontrado " << std::endl;
         polos.push_back(*it);
      }

   }

   v.clear();

   // GENERAMOS PERFIL (VERTICES)
   for (int j = 0; j < num_instancias; j++)
   {

      float angulo = (2 * M_PI / num_instancias) * j;

      for (int k = 0; k < perfil_original.size(); k++)
      {

         float x = perfil_original[k](X) * cos(angulo) + perfil_original[k](Z) * sin(angulo);
         float z = perfil_original[k](X) * -sin(angulo) + perfil_original[k](Z) * cos(angulo);
         float y = perfil_original[k](Y);

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

   int pos_polo_norte = perfil_original.size() - 1;
   int pos_polo_sur = 0;

   if (polos.size() > 0)
   {

      //std::cout << "Posicion polo norte: " << pos_polo_norte << std::endl;
      //std::cout << "Posicion polo sur: " << pos_polo_sur << std::endl;

      // Generamos ambas tapas

      tapaSuperior(perfil_original, num_instancias, pos_polo_norte);
      tapaInferior(perfil_original, num_instancias, pos_polo_sur);
   }
   else
   { // Si nada más que hay un polo tenemos que ver si es superior o inferior y dibujar la tapa

      // std::cout << "Posicion polo norte: " << pos_polo_norte << std::endl;
      // std::cout << "Posicion polo sur: " << pos_polo_sur << std::endl;
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

   f.push_back({(int)perfil_original.size() * (num_instancias - 1), sur, 0});
}