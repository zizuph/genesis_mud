inherit "/std/room";

#include "defs.h"

void
create_room()
{
    set_short("Around tower");
    set_long(break_string(
	  "You are east of the southernmost white tower. The path "
	+ "you are on encircles both towers. The tower looks just "
	+ "like its twin brother.\n",70));

    add_item(({"tower","white tower"}), break_string(
	  "The white tower and the one north of it have both been built "
	+ "ages ago as watchtowers. From above you can probably see "
	+ "far around.\n", 70));

    add_item(({"path","paths"}), break_string(
	  "The path encircles both towers. Many feet have crossed it, "
	+ "but now the grass is growing back.\n",70));

    add_exit(STAND_DIR + "path10", "north");
    add_exit(STAND_DIR + "path8", "south");
}
