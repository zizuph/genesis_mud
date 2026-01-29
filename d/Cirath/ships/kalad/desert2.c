 /* /d/Cirath/ships/kalad/desert2.c
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
  set_long("Unbroken desert stretches from horizon to horizon"+
    "... dry winds and blowing sands greet all who enter the "+
    "Great Kalad Waste.\n");

  add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
  OUTSIDE;
  ADD_SUN_ITEM;
}
