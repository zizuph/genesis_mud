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
	string exit_left = "southwest";

    add_road();
    add_twoway_road_string(exit_left, exit_right);
	add_extra_string_end("The road ascends more steeply towards the hold " +
	"here as it begins its switchback around the cliffside.");

    reset_faerun_room();

    add_exit(ROOM_DIR + "thornhold_road_04",   exit_right);
    add_exit(ROOM_DIR + "thornhold_road_06",   exit_left);

    set_no_exit_msg(({"northwest", "west"}),
    "A sheer cliff blocks progress in that direction, as the " +
    "road to Thornhold ascends towards the fortress in a steep " +
    "switchback.\n");

    set_no_exit_msg(({"northeast", "north"}),
    "Treacherous scree yields to a precipitous drop down onto " +
    "the Mere of Dead Men in that direction. It is too perilous " +
    "to attempt to climb down there from here.\n");

    set_no_exit_msg(({"south", "southeast"}),
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
