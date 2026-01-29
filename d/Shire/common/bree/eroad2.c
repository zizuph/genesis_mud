#include "defs.h"

inherit "std/room";

create_room() {
    set_short("road");
    set_long(break_string(
	  "You are on the well-travelled Eastroad. "
	+ "To the south are scary hills, covered in fog. "
	+ "West you see a bridge crossing a river.\n",70));

    add_exit(STAND_DIR + "eroad1", "east");
    add_exit(STAND_DIR + "bridge1", "west");
    add_exit(STAND_PARENT + "downs/slope3", "south");
}
