inherit "/std/room";

#include "defs.h"

void
create_room()
{
    set_short("Around tower");
    set_long(break_string(
	  "You are northwest of the northernmost white tower. The path "
	+ "you are on encircles the towers. Some rabbit has dug a "
	+ "hole here.\n",70));

    add_item(({"tower","white tower"}), break_string(
	  "The white tower and its twin have both been built a long "
	+ "time ago as watchtowers. It is said that one can see for "
	+ "miles around from the top.\n", 70));

    add_item(({"path","paths"}), break_string(
	  "The path encircles both towers. Many feet have crossed it, "
	+ "but now the grass is growing back.\n",70));

    add_exit(STAND_DIR + "path1", "east");
    add_exit(STAND_DIR + "path3", "south");

    clone_object(STAND_DIR + "rabbithole")->move(this_object());
}
