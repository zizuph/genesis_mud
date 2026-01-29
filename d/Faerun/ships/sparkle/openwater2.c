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
  set_short("Along the western coast of Faerun");
  set_long(short() + ". The water is choppy and waves slap against the side of the ship as it cuts through the sea. A few birds follow drift overhead.\n");
  add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
}
