#include "auxiliar.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado=1)
{
   Tupla3f c0 ( 0.0f , 0.0f , 0.0f );
   Tupla3f c1 ( lado , 0.0f , 0.0f );
   Tupla3f c2 ( lado , lado , 0.0f );
   Tupla3f c3 ( 0.0f , lado , 0.0f );

   Tupla3f c4 ( 0.0f , 0.0f , lado );
   Tupla3f c5 ( lado , 0.0f , lado);
   Tupla3f c6 ( lado , lado , lado );
   Tupla3f c7 ( 0.0f , lado , lado );

   v.resize(8);
   v = {c0, c1, c2, c3, c4, c5, c6, c7};

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

   Tupla3i cc0 ( 3 , 2 , 1 ); // CARA CUBO
   Tupla3i cc1 ( 1 , 0 , 3 );
   Tupla3i cc2 ( 0 , 1 , 4 );   
   Tupla3i cc3 ( 4 , 1 , 5 );
   Tupla3i cc4 ( 5 , 1 , 6 );
   Tupla3i cc5 ( 1 , 2 , 6 );
   Tupla3i cc6 ( 6 , 2 , 7 );
   Tupla3i cc7 ( 7 , 2 , 3 );

   // TAPA SUPERIOR
   Tupla3i cc8 ( 7 , 3 , 0 );  
   Tupla3i cc9 ( 4 , 7 , 0 );

   // TAPA INFERIOR
   Tupla3i cc10( 5 , 7 , 4 );
   Tupla3i cc11( 5 , 6 , 7 );

   f.resize(12);
   f = {cc0, cc1, cc2, cc3, cc4, cc5, cc6, cc7, cc8, cc9, cc10, cc11};

   c_p.resize(8);
   c_l.resize(8);
   c_s.resize(8);

   Tupla3f rojo  ( 1 , 0 , 0 );
   Tupla3f verde ( 0 , 1 , 0 );
   Tupla3f azul  ( 0 , 0 , 1 );

   color_puntos(rojo);

   color_lineas(verde);

   color_solido(azul);

   // // CUBO RGB
   // Tupla3f c0_rgb ( 0.0f , 0.0f , 0.0f );
   // Tupla3f c1_rgb ( 1.0f , 0.0f , 0.0f );
   // Tupla3f c2_rgb ( 1.0f , 1.0f , 0.0f );
   // Tupla3f c3_rgb ( 0.0f , 1.0f , 0.0f );

   // Tupla3f c4_rgb ( 0.0f , 0.0f , 1.0f );
   // Tupla3f c5_rgb ( 1.0f , 0.0f , 1.0f );
   // Tupla3f c6_rgb ( 1.0f , 1.0f , 1.0f );

   // Tupla3f c7_rgb ( 0.0f , 1.0f , 1.0f );

   // c_s.resize(8);
   // c_s = {c0_rgb, c1_rgb, c2_rgb, c3_rgb, c4_rgb, c5_rgb, c6_rgb, c7_rgb};

   calcularNormales();

   ct.resize(v.size());

   Tupla2f ct0 (0.0f, 0.0f);
   Tupla2f ct1 (1.0f, 0.0f);
   Tupla2f ct2 (0.0f, 1.0f);
   Tupla2f ct3 (1.0f, 1.0f);
   Tupla2f ct4 (0.0f, 0.0f);
   Tupla2f ct5 (1.0f, 0.0f);
   Tupla2f ct6 (0.0f, 1.0f);
   Tupla2f ct7 (1.0f, 1.0f);

   ct = {ct0, ct1, ct2, ct3, ct4, ct5, ct6, ct7};

   // this->tipotext = PLANA;

   // calcularCoordTextura(tipotext);

}