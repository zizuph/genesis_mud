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


  add_exit(RIDGE_DESERT+"d35.c","east",0,1,0);
  add_exit(RIDGE_DESERT+"d30.c","northeast",0,1,0);
  add_exit(RIDGE_DESERT+"d29.c","north",0,1,0);
  add_exit(RIDGE_DESERT+"d28.c","northwest",0,1,0);
  add_exit(RIDGE_DESERT+"d33.c","west",0,1,0);
  add_exit(RIDGE_DESERT+"d38.c","southwest",0,1,0);

}


