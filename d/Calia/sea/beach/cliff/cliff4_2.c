/*  description: Room on a cliff above Calian sea
 *  coder: Tigerlily
 *  date:  2002-01-05
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
    make_cliff_room(2);
    add_exit(CLIFF_ROOM + "cliff4_1", "down",
      &navigate_cliff(), &calc_fatigue(), 1);
    add_exit(CLIFF_ROOM + "cliff3_2", "left",
      &navigate_cliff(), &calc_fatigue(), 1);
    add_item(({"down", "downward", "below"}),
      "You glance down and notice that it is possible"+
      " to descend here.\n");
    add_item(({"left", "to the left"}),
      "You look to the left and observe"+
      " that the rock surface gives some"+
      " purchase to proceed in that direction.\n");


}
