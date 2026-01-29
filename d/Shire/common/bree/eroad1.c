#include "defs.h"

inherit "std/room";

create_room() {
    set_short("road");
    set_long(break_string(
	  "You are on the Great Eastroad. "
	+ "East are the gates of the little village Bree. "
	+ "The road leads west towards the rest of the Shire, "
	+ "past the Barrow Downs...\n",70));

    add_exit(STAND_DIR + "cross", "east");
    add_exit(STAND_DIR + "eroad2", "west");
}
