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
  set_short("North of the Moonshae Isles of Faerun");
  set_long(short() + ". They rise in the distance. They are a group of islands that form a rough, circular archipelago off the Sword Coast. Seawater sprays up as waves hit the side of ship.\n");
  add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
}
