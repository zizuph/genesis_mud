 /* A base hall room */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"


void
create_inside_room()
{

}

void
create_room()
{


  set_short("A room");
  set_long("A room.\n");
  create_inside_room();

  INSIDE

}

