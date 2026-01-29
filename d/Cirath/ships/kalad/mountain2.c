 /* /d/Cirath/ships/kalad/mountain2.c
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
  set_long("Towering mountains dominate the rugged "+
    "landscape. The wagon-road dips and swerves around "+
    "ancient rock formations and deadly cliffs.\n");

  add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
  OUTSIDE;
  ADD_SUN_ITEM;
}
