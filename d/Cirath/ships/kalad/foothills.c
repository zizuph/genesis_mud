 /* /d/Cirath/ships/kalad/foothills.c
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
  set_short("Barren foothills");
  set_long("Pathetic scrub clings to the last remnants of "+
    "soil on these nearly completely bare foothills. "+
  "The blowing desert sands from the west carve into these "+
  "hills, while to the east looms a mountain range.\n");

  add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
  OUTSIDE;
  ADD_SUN_ITEM;
}
