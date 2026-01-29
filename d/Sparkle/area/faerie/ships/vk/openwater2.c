/*
 * Water room for ships
 * -- Finwe, January 2006
 */

inherit "/std/room.c";

#include "defs.h"
#include <stdproperties.h>

create_room()
{
  set_short("Somewhere in the middle of a lake in Faerie");
  set_long("Somewhere in the middle of a lake in Faerie.\n");
  add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
}
