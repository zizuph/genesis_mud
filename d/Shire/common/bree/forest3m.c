#include "defs.h"

inherit "/std/room";

create_room() {
    set_short("Forest");
    set_long(break_string(
	  "The scary trees seem to be surrounding you. "
	+ "Obviously they do not like strangers in their domain. "
	+ "You wish you were somewhere else, if only you could find your "
	+ "way out of this place.\n",70));

    add_item(({"tree","trees"}), break_string(
	  "The trees seem to be looking straight at you, and you feel "
	+ "frightened by them. You can only fix your mind on getting out "
	+ "of here as soon as possible.\n",70));

    add_item(({"branch","branches"}), break_string(
	  "The branches of the trees seem to come in your direction "
	+ "whenever you pass them. They are quite scary.\n",70));

    add_exit(STAND_DIR + "forest4", "west");
    add_exit(STAND_DIR + "forest3m", "east");
    add_exit(STAND_DIR + "forest3n", "north");
    add_exit(STAND_DIR + "forest3s", "south");
}
