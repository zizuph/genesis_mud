#include "defs.h"

inherit "/std/room";

create_room() {
    set_short("Forest");
    set_long(break_string(
	  "You are in the northern part of the scary old forest. "
	+ "To the north the bushes seem to grow denser. "
	+ "You don't like this forest anymore...\n",70));

    add_item(({"tree","trees"}), break_string(
	  "The trees seem to be looking straight at you, and you feel "
	+ "frightened by them. You can only fix your mind on getting out "
	+ "of here as soon as possible.\n",70));

    add_item(({"branch","branches"}), break_string(
	  "The branches of the trees seem to come in your direction "
	+ "whenever you pass them. They are quite scary.\n",70));

    add_exit(STAND_DIR + "forest2n", "west");
    add_exit(STAND_DIR + "forest1n", "east");
    add_exit(STAND_DIR + "forest2n", "north");
    add_exit(STAND_DIR + "forest1m", "south");
}
