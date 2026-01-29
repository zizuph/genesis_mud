 /* A base tower room */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"


void
create_outside_room()
{

}

void
create_room()
{


  set_short("Outside");
  set_long("Outside.\n");
  create_outside_room();

  OUTSIDE

}

