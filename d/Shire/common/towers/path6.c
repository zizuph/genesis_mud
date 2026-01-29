inherit "/std/room";

#include "defs.h"

void
create_room()
{
    set_short("Around tower");
    set_long(break_string(
	  "You are southwest of the southernmost white tower. The path "
	+ "bends around the tower here.\n",70));

    add_item(({"tower","white tower"}), break_string(
	  "The white tower and its twin have both been built a long "
	+ "time ago as watchtowers.\n", 70));

    add_item(({"path","paths"}), break_string(
	  "The path encircles both towers. Many feet have crossed it, "
	+ "but now the grass is growing back.\n",70));

    add_exit(STAND_DIR + "path5", "north");
    add_exit(STAND_DIR + "path7", "east");
}
