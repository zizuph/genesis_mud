 /* /d/Cirath/ships/roke/air1.c
  * A 'water' room for the Tyr-Roke line to pass through.
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
  set_short("Flying through the sky");
  set_long("The sun sparkles brightly through drifting "+
    "clouds into your eyes, as the roc flies with "+
    "deceptive speed through the heavens.  Far below, "+
    "scattered islands seem overwhelmed by the vast "+
    "oceans surrounding them.\n");

  add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
  OUTSIDE;
  ADD_SUN_ITEM;
}
