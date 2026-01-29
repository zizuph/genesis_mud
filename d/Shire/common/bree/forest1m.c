#include "defs.h"

inherit "/std/room";

create_room() {
    set_short("Forest");
    set_long(break_string(
	  "You have entered the old, gloomy forest west of Bree. "
	+ "The trees seem very much alive, "
	+ "stretching their branches after you. "
	+ "You wonder if there really is a way out of here...\n",70));

    add_item(({"tree","trees"}), break_string(
	  "The trees seem to be looking straight at you, and you feel "
	+ "frightened by them. You can only fix your mind on getting out "
	+ "of here as soon as possible.\n",70));

    add_item(({"branch","branches"}), break_string(
	  "The branches of the trees seem to come in your direction "
	+ "whenever you pass them. They are quite scary.\n",70));

    add_exit(STAND_DIR + "forest2m", "west");
    add_exit(STAND_DIR + "forest1m", "east");
    add_exit(STAND_DIR + "forest1n", "north");
    add_exit(STAND_DIR + "forest1s", "south");
}
