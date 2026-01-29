 /* /d/Cirath/ships/kalad/desert4.c
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
  set_short("In the desert");
  set_long("The wagon passes a large city. You see large "+
    "red-coloured banners wavering in the wind on top of "+
    "several spires that reach towards the clouds. "+
    "Several armoured humans seem to linger their eyes on "+
    "the wagon - to make sure noone tries to leave it. They "+
    "do not seem to want visitors. You wonder how much the "+
    "trading company has paid to be allowed passage "+
    "through this city-state.\n");

  add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
  OUTSIDE;
  ADD_SUN_ITEM;
}
