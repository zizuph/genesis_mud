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

    make_cliff_room(4);

    add_exit(CLIFF_ROOM + "cliff_ledge", "up",
      &navigate_cliff(), &calc_fatigue(), 1);
    add_exit(CLIFF_ROOM + "cliff0_3", "down",
      &navigate_cliff(), &calc_fatigue(), 1);
    add_item(({"up", "upward", "above"}),
      "You glance up and notice that it is possible"+
      " to ascend here.\n");

    add_item(({"down", "downward", "below"}),
      "You glance down and notice that it is possible"+
      " to descend here.\n");


}
