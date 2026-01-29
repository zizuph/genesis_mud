#include "defs.h"

inherit "/std/room";

create_room() {
    set_short("Forest");
    set_long(break_string(
	  "You are in the middle of the southern part of the old forest. "
	+ "The dangerous-looking trees try to prevent you from going back. "
	+ "You feel the powers of some ancient wisdom dragging you "
	+ "west.\n",70));

    add_item(({"tree","trees"}), break_string(
	  "The trees seem to be looking straight at you, and you feel "
	+ "frightened by them. You can only fix your mind on getting out "
	+ "of here as soon as possible.\n",70));

    add_item(({"branch","branches"}), break_string(
	  "The branches of the trees seem to come in your direction "
	+ "whenever you pass them. They are quite scary.\n",70));

    add_exit(STAND_DIR + "forest3s", "west");
    add_exit(STAND_DIR + "forest2s", "east");
    add_exit(STAND_DIR + "forest2m", "north");
    add_exit(STAND_DIR + "forest3s", "south");
}
