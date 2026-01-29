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
  set_short("Somewhere in the Gulf of Lune");
  set_long(short() + ".\n");
  add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
}
