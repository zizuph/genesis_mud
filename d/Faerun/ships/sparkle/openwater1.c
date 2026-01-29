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
  set_short("Near the western coast of Faerun");
  set_long(short() + ". Tall trees grow along the shore, hiding the coast line from view. There are usually hidden coves and inlets used by pirates and ship captains. The fresh smell of evergreens and saltwater blows in the wind.\n");
  add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
}
