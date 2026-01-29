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
    string exit_left = "north";

    add_road();
    add_extra_string_end("The road may be followed through " +
        "north to the gates of Thornhold or along a ridge " +
        "to the south.");

    reset_faerun_room();

    add_exit(ROOM_DIR + "thornhold_road_08", exit_right);
    add_exit(ROOM_DIR + "gate", exit_left);

    set_no_exit_msg(({"northeast"}),
    "A steep incline littered with treacherous scree renders " +
    "Thornhold unreachable save by approaching the gate.\n");

    set_no_exit_msg(({"east", "southeast"}),
    "You see a gap in the rocks that yields to a treacherous " +
    "embankment leading to the Mere of Dead Men, but it is " +
    "littered with loose and jagged rock that renders passage " +
    "in that direction impossible.\n");
    
    set_no_exit_msg(({"northwest"}),
    "You attempt to step onto the ledge that hugs the perimeter of " +
    "the west tower, but your foot slips and nearly sends you tumbling " +
    "off the cliff! You regain your footing and step back onto the " +
    "road.\n");

    set_no_exit_msg(({"west", "southwest"}),
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
