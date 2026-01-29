inherit "/std/room";

#include "defs.h"

void
create_room()
{
    set_short("Around tower");
    set_long(break_string(
	  "You are southwest of the northernmost white tower, and "
	+ "northwest of its twin. The path "
	+ "you are on encircles both towers and also runs between "
	+ "them, to the entrances. Both towers must be ancient, "
	+ "but still gleam with a white glow. East are the entrances "
	+ "of both towers.\n",70));

    add_item(({"tower","white tower", "entrances"}), break_string(
	  "The white tower and its twin have both been built a long "
	+ "time ago as watchtowers. It is said that one can see for "
	+ "miles around from the top. Their entrances face each "
	+ "other.\n", 70));

    add_item(({"path","paths"}), break_string(
	  "The path encircles both towers. Many feet have crossed it, "
	+ "but now the grass is growing back. The path splits in three "
	+ "directions here: east to the entrances, and north and south "
	+ "around the towers.\n",70));

    add_exit(STAND_DIR + "path3", "north");
    add_exit(STAND_DIR + "path5", "south");
    add_exit(STAND_DIR + "path13", "east");
}
