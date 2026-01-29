 /* /d/Cirath/ships/roke/air6.c
  * A 'water' room for the Tyr-Roke line to run through.
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
  set_short("Flying through the sky");
  set_long("The sun sparkles brightly through drifting "+
    "clouds into your eyes, as the roc flies with deceptive "+
    "speed through the heavens. "+
    "Far below, barren foothills separate a bleak desert "+
    "from a jagged mountain range to the south.\n");

  add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
  OUTSIDE;
  ADD_SUN_ITEM;
}
