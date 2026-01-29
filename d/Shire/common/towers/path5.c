inherit "/std/room";

#include "defs.h"

void
create_room()
{
    set_short("Around tower");
    set_long(break_string(
	  "You are west of the southernmost white tower. The path "
	+ "you are on encircles both towers. This tower is an exact "
	+ "replica of the other.\n",70));

    add_item(({"tower","white tower"}), break_string(
	  "The white tower and its twin have both been built a long "
	+ "time ago as watchtowers. From above you can probably see "
	+ "far around.\n", 70));

    add_item(({"path","paths"}), break_string(
	  "The path encircles both towers. Many feet have crossed it, "
	+ "but now the grass is growing back.\n",70));

    add_exit(STAND_DIR + "path4", "north");
    add_exit(STAND_DIR + "path6", "south");
}
