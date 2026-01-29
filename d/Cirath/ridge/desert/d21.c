 /* The desert, just west of Tyr.
  * Decius, December 1997
  */

#pragma strict_types
#pragma save_binary

#include "defs.h"

inherit BASE_DESERT;

void
create_desert()
{


  add_exit(RIDGE_DESERT+"d22.c","east",0,1,0);
  add_exit(RIDGE_DESERT+"d18.c","northeast",0,1,0);
  add_exit(RIDGE_DESERT+"d17.c","north",0,1,0);
  add_exit(RIDGE_DESERT+"d16.c","northwest",0,1,0);
  add_exit(RIDGE_DESERT+"d20.c","west",0,1,0);
  add_exit(RIDGE_DESERT+"d24.c","southwest",0,1,0);
  add_exit(RIDGE_DESERT+"d25.c","south",0,1,0);
  add_exit(RIDGE_DESERT+"d16.c","southeast",0,1,0);

}


