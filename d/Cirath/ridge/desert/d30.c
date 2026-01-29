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


  add_exit(RIDGE_DESERT+"d31.c","east",0,1,0);
  add_exit(RIDGE_DESERT+"d26.c","northeast",0,1,0);
  add_exit(RIDGE_DESERT+"d25.c","north",0,1,0);
  add_exit(RIDGE_DESERT+"d24.c","northwest",0,1,0);
  add_exit(RIDGE_DESERT+"d29.c","west",0,1,0);
  add_exit(RIDGE_DESERT+"d34.c","southwest",0,1,0);
  add_exit(RIDGE_DESERT+"d35.c","south",0,1,0);

}


