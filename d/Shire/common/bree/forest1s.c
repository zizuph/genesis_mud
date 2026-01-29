#include "defs.h"

inherit "/std/room";

create_room() {
    set_short("Forest");
    set_long(break_string(
	  "You are in the south part of an old oak forest. "
	+ "The trees seem to gather around you and you wish you "
	+ "had never entered it in the first place... To the "
	+ "south the bushes seem almost impregnable.\n",70));

    add_item(({"tree","trees"}), break_string(
	  "The trees seem to be looking straight at you, and you feel "
	+ "frightened by them. You can only fix your mind on getting out "
	+ "of here as soon as possible.\n",70));

    add_item(({"branch","branches"}), break_string(
	  "The branches of the trees seem to come in your direction "
	+ "whenever you pass them. They are quite scary.\n",70));

    add_exit(STAND_DIR + "forest2s", "west");
    add_exit(STAND_DIR + "forest1s", "east");
    add_exit(STAND_DIR + "forest1m", "north");
    add_exit(STAND_DIR + "forest2s", "south");
}
