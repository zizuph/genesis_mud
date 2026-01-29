inherit "/std/room";

#include "defs.h"

void
create_room()
{
    set_short("Around tower");
    set_long(break_string(
	  "You are at the base of a big white tower. Behind it, on "
	+ "the southside, is another one just like it. To the north "
	+ "is the Eastroad, west and east are grass paths that lead "
	+ "around the tower.\n", 70));

    add_item(({"tower","white tower"}), break_string(
	  "The white tower and its twin have both been built a long "
	+ "time ago as watchtowers. It is said that one can see for "
	+ "miles around from the top.\n", 70));

    add_item(({"path","paths"}), break_string(
	  "The paths encircle both towers. Many feet have crossed them, "
	+ "but now the grass is growing back.\n",70));

    add_exit(STAND_PARENT + "greyhaven/gh4", "north");
    add_exit(STAND_DIR + "path12", "east");
    add_exit(STAND_DIR + "path2", "west");
}
