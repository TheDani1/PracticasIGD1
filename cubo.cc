#include "auxiliar.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{
   Tupla3f c0 ( -lado/2.0f , -lado/2.0f , -lado/2.0f );
   Tupla3f c1 ( +lado/2.0f , -lado/2.0f , -lado/2.0f );
   Tupla3f c2 ( -lado/2.0f , -lado/2.0f , +lado/2.0f );
   Tupla3f c3 ( +lado/2.0f , -lado/2.0f , +lado/2.0f );

   Tupla3f c4 ( -lado/2.0f , lado/2.0f , -lado/2.0f );
   Tupla3f c5 ( +lado/2.0f , lado/2.0f , -lado/2.0f );
   Tupla3f c6 ( -lado/2.0f , lado/2.0f , +lado/2.0f );
   Tupla3f c7 ( +lado/2.0f , lado/2.0f , +lado/2.0f );

   v.resize(8);
   v = {c0, c1, c2, c3, c4, c5, c6, c7};

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

   Tupla3i cc0 ( 3 , 7 , 6 ); // CARA CUBO
   Tupla3i cc1 ( 3 , 6 , 2 );
   Tupla3i cc2 ( 2 , 6 , 4 );   
   Tupla3i cc3 ( 2 , 4 , 0 );
   Tupla3i cc4 ( 1 , 0 , 4 );
   Tupla3i cc5 ( 1 , 4 , 5 );
   Tupla3i cc6 ( 1 , 5 , 7 );
   Tupla3i cc7 ( 1 , 7 , 3 );

   // TAPA SUPERIOR
   Tupla3i cc8 ( 7 , 5 , 4 );  
   Tupla3i cc9 ( 7 , 4 , 6 );

   // TAPA INFERIOR
   Tupla3i cc10( 2 , 0 , 3 );
   Tupla3i cc11( 3 , 0 , 1 );

   f.resize(12);
   f = {cc0, cc1, cc2, cc3, cc4, cc5, cc6, cc7, cc8, cc9, cc10, cc11};

   c.resize(8);

   Tupla3f cv0 ( 1 , 0 , 0 ); // COLOR VERTICE
   Tupla3f cv1 ( 1 , 0 , 0 );
   Tupla3f cv2 ( 1 , 0 , 0 );   
   Tupla3f cv3 ( 1 , 0 , 0 );
   Tupla3f cv4 ( 1 , 0 , 0 );
   Tupla3f cv5 ( 1 , 0 , 0 );
   Tupla3f cv6 ( 1 , 0 , 0 );
   Tupla3f cv7 ( 1 , 0 , 0 );

   c = {cv0, cv1, cv2, cv3, cv4, cv5, cv6, cv7};

}