#pragma strict_types

inherit "/d/Gondor/common/room.c";
inherit "/d/Gondor/anorien/osgiliath/osgiliath";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_room()
{
    set_short("in a dark corridor in the ruins of Central Osgiliath");
    set_long(BSN("This is a stairwell leading up and down, "
      + "though the way down is collapsed. A corridor leads north "
      + "between old walls of stone. The narrow stairway leads up into "
      + "the upper parts of the building."));
    add_prop(ROOM_M_NO_TELEPORT, check_teleport);
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);
    add_item(({"torch-stands","stands","torch-stand","stand"}),BSN("They are "+
    "made of metal rings, now rusty beyond being usable."));
    add_item("walls",BSN("The walls are made of smooth white stone, though "+
    "the passage of hundreds of years since repair have left solid tracks."));
    add_item(({"stairs","stair","stairway","staircase"}), BSN(
    "This narrow staircase is made of ancient gray stone. There " +
    "is a slight depression in the middle of each step of the stairway, " +
    "marking the passage of thousands of feet."));
    add_item(({"step","steps"}), BSN(
    "The steps are each composed of a single large stone which has " +
    "been worn smooth by the tread of numerous feet over the years."));
    add_exit(OSG_DIR+"w3stairway",   "up",   0, 3);
    add_exit(OSG_DIR+"w1archway",   "down",  0, 2);
    add_exit(OSG_DIR+"w2corridor1", "north", 0, 1);
}


