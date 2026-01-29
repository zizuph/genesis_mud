inherit "/std/room";

#include "defs.h"

/* Prototypes */
void reset_room();

void
create_room()
{
    set_short("Around tower");
    set_long(break_string(
	  "You are west of the northernmost white tower. The path "
	+ "you are on encircles both towers. You are impressed by "
	+ "the height of the tower.\n",70));

    add_item(({"tower","white tower"}), break_string(
	  "The white tower and its twin have both been built a long "
	+ "time ago as watchtowers. It is said that one can see for "
	+ "miles around from the top.\n", 70));

    add_item(({"path","paths"}), break_string(
	  "The path encircles both towers. Many feet have crossed it, "
	+ "but now the grass is growing back.\n",70));

    add_exit(STAND_DIR + "path2", "north");
    add_exit(STAND_DIR + "path4", "south");
    reset_room();
}

void
reset_room()
{
    if (!present("bucket"))
	clone_object(STAND_OBJ + "bucket")->move(this_object());
}
