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
  set_long(short() + ". It stretches out before you in all directions. The ship cuts through the water as it travels across the water. In the distance, fish fly out of the water and disappear beneath the surface.\n");
  add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
}
