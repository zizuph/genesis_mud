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
  set_short("Out in the Trackless Sea");
  set_long(short() + ". The ship sails through the wide expanse of water, rising and falling in the sea's waves. The sea fills the horizon, stretching in all directions. Porpoises race in front, some leaping and spinning in the air before diving into the sea.\n");
  add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
}
