inherit "/std/room";

#include "defs.h"

void
create_room()
{
    set_short("Around tower");
    set_long(break_string(
	  "You are southeast of the northernmost white tower, and "
	+ "northeast of its twin. This path "
	+ "encircles both towers and also runs between them to the "
	+ "entrances. From here, both towers look magnificent "
	+ "and powerful.\n",70));

    add_item(({"tower","white tower", "entrances"}), break_string(
	  "The white tower and its twin have both been built a long "
	+ "time ago as watchtowers. It is said that one can see for "
	+ "miles around from the top. Their entrances face each "
	+ "other.\n", 70));

    add_item(({"path","paths"}), break_string(
	  "The path encircles both towers. Many feet have crossed it, "
	+ "but now the grass is growing back. The path splits in three "
	+ "directions here: west to the entrances, and north and south "
	+ "around the towers.\n",70));

    add_exit(STAND_DIR + "path11", "north");
    add_exit(STAND_DIR + "path9", "south");
    add_exit(STAND_DIR + "path13", "west");
}
