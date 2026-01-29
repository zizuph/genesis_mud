#include "defs.h"

inherit LAKESHORE_ROOM;

void
create_lakeshore_room()
{
    set_short("By the lakeshore");
    set_em_long("You are on a clean and well kept cobblestone path " +
		"following the shoreline. The view of the lake shore " +
		"is breath taking. Snow capped peaks far in the " +
		"distance compliment the crystal clear blue waters " +
		"of lake perfectly. The lake side path continues to " +
		"the east and west. The city is directly south.\n");
    add_item(({"lake", "waters", "water"}),
	     "The lake water is crystal pure.\n");
    add_item(({"path", "cobblestone", "cobblestone path"}),
	     "The cobblestone path is nearly spotless. " +
	     "The Telberin elves must really pride themselves " +
	     "in cleanliness.\n");
    add_item(({"peak", "peaks"}),
	     "The majestic white peaks seem to rise out of the water " +
	     "on the far end of the lake.\n");
    add_exit("beach02", "east");
    add_exit("beach16", "west");
    add_exit(TELBERIN_DIR + "tel10_19", "south");
}
