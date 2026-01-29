 /* A base desert room */

#pragma save_binary
#pragma strict_types

inherit "/d/Cirath/std/room";

#include "defs.h"


void
create_desert()
{

}

void
create_room()
{


  set_short("A desert west of Tyr");
  set_long("A desert west of Tyr.\n");
  create_desert();

  OUTSIDE
  LIGHT
  ADD_SUN_ITEM

}

