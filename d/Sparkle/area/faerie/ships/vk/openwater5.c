/*
 * Water room for ships
 * -- Finwe, January 2006
 */

inherit "/std/room.c";

#include "defs.h"
#include <stdproperties.h>

create_room()
{
  set_short("Out in the open sea");
  set_long("Out in the open sea.\n");
  add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
}
