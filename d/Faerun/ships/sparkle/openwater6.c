/*
 * Water room for ships
 * -- Finwe, January 2006
 */

inherit "/std/room.c";

#include "defs.h"
#include "/d/Faerun/defs.h"
#include <stdproperties.h>

create_room()
{
  set_short("Along the coast of Sparkle");
  set_long(short() + ". Water foams from all the countless ships that pass this way. Piers jut out into the water and waves lap around them. \n");
  add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
}
