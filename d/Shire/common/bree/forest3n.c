#include "defs.h"

inherit "/std/room";

create_room() {
    set_short("Forest");
    set_long(break_string(
	  "This really looks bad. All around you, you see "
	+ "nothing but evil-looking trees, who seem to be peering at you. "
	+ "There most certainly is some kind of power at work here. "
	+ "It seems to be dragging you in its direction...\n",70));

    add_item(({"tree","trees"}), break_string(
	  "The trees seem to be looking straight at you, and you feel "
	+ "frightened by them. You can only fix your mind on getting out "
	+ "of here as soon as possible.\n",70));

    add_item(({"branch","branches"}), break_string(
	  "The branches of the trees seem to come in your direction "
	+ "whenever you pass them. They are quite scary.\n",70));

    add_exit(STAND_DIR + "forest4", "west");
    add_exit(STAND_DIR + "forest3n", "east");
    add_exit(STAND_DIR + "forest4", "north");
    add_exit(STAND_DIR + "forest3m", "south");
}
