 /* /d/Cirath/ships/kalad/desert1.c
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
  set_long("A lonely wagon-road winds it's way through "+
    "uncounted miles of dreary desert underneath the hot "+
    "kaladian sun. Scanning the horizon reveals a distant "+
    "line of hills to the east, and more desert in every "+
    "other direction.\n");

  add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
  OUTSIDE;
  ADD_SUN_ITEM;
}
