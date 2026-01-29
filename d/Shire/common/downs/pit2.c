inherit "/d/Shire/room";

#include "/d/Shire/common/defs.h"
#include "stdproperties.h"

create_room() {
    set_short("beneath the Barrow Downs");
    set_long(break_string(
	  "You are now somewhere in the lower parts of this down. "
	+ "The hole you came from looks like a black eye staring straight "
	+ "at you. Perhaps you should leave this place alone. To the "
	+ "south you catch a glimpse of daylight...\n",70));

    add_exit(DOWNS_DIR + "down4", "south");
    add_exit(DOWNS_DIR + "pit", "up");

    add_item("hole", "The hole is black as the void....and a stinky smell "+
	"comes down from it!\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
}
