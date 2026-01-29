 /* /d/Cirath/ships/kalad/mountain1.c
  * A 'water' room for the Tyr-Kalad line to run through.
  * Decius, November 1996
  */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include "ship.h"

void
create_room()
{
  set_short("Within the mountains");
  set_long("This thin wagon-road winds around looming "+
  "mountains on one side, and skirts deep canyons on the other.\n");

  add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
  OUTSIDE;
  ADD_SUN_ITEM;
}
