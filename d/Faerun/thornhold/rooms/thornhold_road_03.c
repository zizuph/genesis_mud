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
	add_extra_string_end("From this vantage point, looking to the east " +
	"you can see the High Road stretching northwest along the mere, while " +
    "to the southeast it cuts a path between the mountains and the sea.");

    set_no_exit_msg(({"north", "west", "northwest", "northeast"}),
    "You attempt to pick a path to climb down to the mere, but find " +
    "no egress due to the treacherous scree.\n");

    set_no_exit_msg(({"south", "southeast"}),
    "You feel along the large and jagged rocks that line the south " +
    "edge of the road, but find no way to climb them.\n");
        
    reset_faerun_room();

    add_exit(ROOM_DIR + "thornhold_road_02",   exit_right);
    add_exit(ROOM_DIR + "thornhold_road_04",   exit_left);
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
