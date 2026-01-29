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
	string exit_right = "northeast";
	string exit_left = "west";

    add_road();
    add_twoway_road_string(exit_left, exit_right);
	add_extra_string_end("The scree at this altitude is more treacherous. " +
	"You can see the High Road stretching northwest along the mere, and " +
    "southeast along the Sword Coast.");

    reset_faerun_room();

    add_exit(ROOM_DIR + "thornhold_road_03",   exit_right);
    add_exit(ROOM_DIR + "thornhold_road_05",   exit_left);

    set_no_exit_msg(({"east"}),
    "A sheer, jagged rock blocks passage in that direction.\n");

    set_no_exit_msg(({"northwest", "north"}),
    "Treacherous scree yields to a precipitous drop down onto " +
    "the Mere of Dead Men in that direction. It is too perilous " +
    "to attempt to climb down there from here.\n");

    set_no_exit_msg(({"southwest", "south", "southeast"}),
    "Sharp and jagged rocks, slick with damp sea air, create a slippery " +
    "embankment that offers no egress in that direction.\n");
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
