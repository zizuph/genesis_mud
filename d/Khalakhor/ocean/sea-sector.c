/*
 * Base sector file
 * Tapakah, 10/2021
 */

#pragma strict_types

#include "defs.h"
#include <stdproperties.h>

inherit ROOM_BASE;

void
create_sea_sector ()
{
  add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
  add_prop(ROOM_I_INSIDE, 0);
  add_prop(ROOM_I_LIGHT, 1);

  set_sink_path(ROOM + "sink_room");
  add_std_exits();
}
