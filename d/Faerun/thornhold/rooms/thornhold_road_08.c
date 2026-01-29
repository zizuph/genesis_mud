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
	string exit_right = "southeast";
	string exit_left = "north";

    add_road();
    add_twoway_road_string(exit_left, exit_right);
    add_extra_string_end("The stone walls and towers of Thornhold " +
	"loom above you.");

    reset_faerun_room();

    add_exit(ROOM_DIR + "thornhold_road_07",   exit_right);
    add_exit(ROOM_DIR + "thornhold_road_09",   exit_left);
    
    set_no_exit_msg(({"northeast"}),
    "A steep incline littered with treacherous scree renders " +
    "Thornhold unreachable save by the road leading north.\n");
    
    set_no_exit_msg(({"east"}),
    "You see a gap in the rocks that yields to a treacherous " +
    "embankment leading to the Mere of Dead Men, but it is " +
    "littered with loose and treacherous rock that renders passage " +
    "in that direction impossible.\n");

    set_no_exit_msg(({"south", "northwest", "west", "southwest"}),
    "You look down at the precipitous cascade of jagged rocks that " +
    "tumble towards the sea, finding no way to proceed in that " +
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
