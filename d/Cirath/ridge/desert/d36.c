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


  add_exit(RIDGE_DESERT+"d37.c","east",0,1,0);
  add_exit(RIDGE_DESERT+"d39.c","southeast",0,1,0);

}


