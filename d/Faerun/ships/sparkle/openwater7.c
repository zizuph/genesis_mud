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
  set_short("Close to the harbour of Sparkle");
  set_long(short() + ". The waves slap against the side of the ship and is cuts through the water. Overhead birds follow the ship as it sails along the harbour of Sparkle.\n");
  add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
}
