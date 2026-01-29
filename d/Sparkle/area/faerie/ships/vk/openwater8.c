/*
 * Water room for ships
 * -- Finwe, January 2006
 */

inherit "/std/room.c";

#include "defs.h"
#include <stdproperties.h>

create_room()
{
  set_short("In the Vingaard River");
  set_long("In the Vingaard River.\n");
  add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
}
