inherit "/std/room";

#include "defs.h"

void
create_room()
{
    set_short("Around tower");
    set_long(break_string(
	  "You are northeast of the northernmost white tower. The path "
	+ "bends around the tower towards the its twin. The tower sure "
	+ "is high from this point of view.\n",70));

    add_item(({"tower","white tower"}), break_string(
	  "The white tower and its twin have both been built a long "
	+ "time ago as watchtowers. It is said that one can see for "
	+ "miles around from the top.\n", 70));

    add_item(({"path","paths"}), break_string(
	  "The path encircles both towers. Many feet have crossed it, "
	+ "but now the grass is growing back.\n",70));

    add_exit(STAND_DIR + "path1", "west");
    add_exit(STAND_DIR + "path11", "south");
}
