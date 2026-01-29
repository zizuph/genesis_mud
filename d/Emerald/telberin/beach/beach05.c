#include "defs.h";

inherit LAKESHORE_ROOM;

void
create_lakeshore_room()
{
    set_short("By the lakeshore next to a gazebo");
    set_em_long("You are on a clean and well kept cobblestone path " +
		"following the shoreline. A large magnificent gazebo " +
		"has been erected to the east right on the edge of the " +
		"shore. Several beautiful white swans grace the peaceful " +
		"blue waters here. The lake side path continues to the " +
		"north and south. The city is directly to the west.\n");
    add_item(({"lake", "waters", "water"}),
	     "The lake water is crystal pure.\n");
    add_item(({"path", "cobblestone", "cobblestone path"}),
	     "The cobblestone path is nearly spotless. " +
	     "The Telberin elves must really pride themselves " +
	     "in cleanliness.\n");
    add_item(({"peak", "peaks"}),
	     "The majestic white peaks seem to rise out of the water " +
	     "on the far end of the lake.\n");
    add_item("gazebo", "The gazebo is beautifully constructed. " +
	     "A pair of swans carved from snow white marble " +
	     "decorate the entrance.\n");
    
    add_exit("beach06", "south");
    add_exit("beach04", "north");
    add_exit("gazebo", "east");
    add_exit(TELBERIN_DIR + "tel19_10", "west");
}
