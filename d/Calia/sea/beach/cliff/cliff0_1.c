/*  description: Room on a cliff above Calian sea
 *  coder: Tigerlily
 *  date:  2002-02-02
 *  special: needs climb skill to access
 *  notes:
 */

#pragma strict_types
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "defs.h"

inherit "/std/room";
inherit BASE_CLIFF;



void
create_room()
{

    make_cliff_room(1);
    add_exit(CLIFF_ROOM + "cliff0_0", "down",
      &navigate_cliff(), calc_fatigue(), 1);
    add_exit(CLIFF_ROOM + "cliff1_1", "right",
      &navigate_cliff(), calc_fatigue(), 1);
    add_item(({"down", "downward", "below"}),
      "You glance down and notice that it might be possible"+
      " to descend here.\n");
    add_item(({"right", "to the right"}),
      "You look to the right and observe"+
      " that the rock surface gives some"+
      " purchase to proceed in that direction.\n");

}
