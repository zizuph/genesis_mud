inherit "/std/room";

#include "defs.h"

void
create_room()
{
    set_short("Between towers");
    set_long(break_string(
	  "You are standing between the two white towers. Their "
	+ "entrances face each other. Each entrance is equipped with "
	+ "a heavy door. The only difference you notice is that the "
	+ "northern door is black, while the door of the southern tower "
	+ "is red. The place between the two towers is paved. "
	+ "East and west paths encircle both towers.\n", 70));

    add_item(({"tower","white tower"}), break_string(
	  "The white tower and its twin have both been built a long "
	+ "time ago as watchtowers. They look like exact replicas. "
	+ "The doors of the towers are north and south.\n", 70));

    add_exit(STAND_DIR + "path10", "east");
    add_exit(STAND_DIR + "path4", "west");
    add_exit(STAND_DIR + "tower11", "north");
    add_exit(STAND_DIR + "tower21", "south");

    clone_object(STAND_DIR + "tower1_doora")->move(this_object());
    clone_object(STAND_DIR + "tower2_doora")->move(this_object());
}
