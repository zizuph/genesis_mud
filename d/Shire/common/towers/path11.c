inherit "/std/room";

#include "defs.h"

void
create_room()
{
    set_short("Around tower");
    set_long(break_string(
	  "You are to the east of the northernmost white tower. The path "
	+ "you are on encircles both towers. Both towers look ancient "
	+ "to you.\n",70));

    add_item(({"tower","white tower"}), break_string(
	  "The white tower and its twin have both been built ages "
	+ "ago as watchtowers. It is said that one can see for "
	+ "miles around from the top.\n", 70));

    add_item(({"path","paths"}), break_string(
	  "The path follows the curve of the tower a bit.\n",70));

    add_exit(STAND_DIR + "path12", "north");
    add_exit(STAND_DIR + "path10", "south");
}
