#include "defs.h"

inherit "/std/room";

create_room() {
    set_short("forest");
    set_long(break_string(
	  "You can see the old forest rise to the west. "
	+ "There are many rumours about that place... "
	+ "It looks inviting, you feel a pull from its heart. "
	+ "An old oak sign.\n",70));

    add_item(({"sign","old sign","oak sign","old oak sign"}), break_string(
	  "It is an old oak sign, with something written on it.\n",70));

    add_exit(STAND_DIR + "forest1m", "west");
    add_exit(STAND_DIR + "road3", "east");
}

init() {
    ::init();
    add_action("do_read", "read");
}

do_read(str) {
    if (str!="sign" && str != "old sign" && str != "old oak sign")
        return; 

    write("The sign says:\n"
        + "Beware of the magic of the old forest.\n");
    return 1;
}
