inherit "/std/room";

#include "defs.h"

void
create_room()
{
    set_short("Around tower");
    set_long(break_string(
	  "You are south of both towers. The southernmost towers "
	+ "obscures your view of the other tower. The path follows "
	+ "the curve of the towerwall.\n",70));

    add_item(({"tower","white tower"}), break_string(
	  "The white tower looks awfully big from so close by.\n",70));

    add_item(({"path","paths"}), break_string(
	  "The path encircles both towers. Many feet have crossed it, "
	+ "but now the grass is growing back.\n",70));

    add_exit(STAND_DIR + "path8", "east");
    add_exit(STAND_DIR + "path6", "west");
}
