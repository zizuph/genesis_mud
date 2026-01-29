/*
 * Road to Thornhold
 * -- Twire/Gnim June 2016
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_ROAD;

void
create_road()
{
	string exit_right = "south";
	string exit_left = "west";

    add_road();
    add_twoway_road_string(exit_left, exit_right);
	add_extra_string_end("Looking over some scree to the east, you " +
	"can see the High Road stretching northwest along the mere, and " +
	"southeast along the Sword Coast.");

    reset_faerun_room();

    add_exit(ROOM_DIR + "thornhold_road_01",   exit_right);
    add_exit(ROOM_DIR + "thornhold_road_03",   exit_left);
    
    set_no_exit_msg(({"northwest"}),
    "You attempt to pick a path to climb down to the mere, but find " +
    "no egress due to the treacherous scree.\n");

    set_no_exit_msg(({"northeast", "east", "north"}),
    "You look for a way to climb back down to the High Road, but find " +
    "no other safe path other than to follow the road south.\n");

    set_no_exit_msg(({"southwest"}),
    "You feel along the large and jagged rocks that line the " +
    "edge of the road, but find no way to climb them.\n");
}

public void
init()
{
    ::init();
}

void
reset_faerun_room()
{
    set_searched(0);
}
