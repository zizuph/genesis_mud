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
	string exit_right = "east";
	string exit_left = "northwest";

    add_road();
    add_twoway_road_string(exit_left, exit_right);
    add_extra_string_end("The west tower of Thornhold peeks " +
	"out from behind a steep rocks before you.");


    reset_faerun_room();

    add_exit(ROOM_DIR + "thornhold_road_06",   exit_right);
    add_exit(ROOM_DIR + "thornhold_road_08",   exit_left);
    
    set_no_exit_msg(({"northeast", "north"}),
    "A steep incline littered with treacherous scree renders " +
    "Thornhold unreachable save by the road leading northwest.\n");

    set_no_exit_msg(({"south", "southeast", "southwest", "west"}),
    "You look down at the precipitous cascade of jagged rocks that " +
    "tumble towards the sea, and find no way to proceed in that " +
    "direction.\n");
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
