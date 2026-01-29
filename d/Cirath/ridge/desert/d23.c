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


  add_exit(RIDGE_DESERT+"d24.c","east",0,1,0);
  add_exit(RIDGE_DESERT+"d20.c","northeast",0,1,0);
  add_exit(RIDGE_DESERT+"d21.c","north",0,1,0);
  add_exit(RIDGE_DESERT+"d28.c","south",0,1,0);
  add_exit(RIDGE_DESERT+"d29.c","southeast",0,1,0);

}


