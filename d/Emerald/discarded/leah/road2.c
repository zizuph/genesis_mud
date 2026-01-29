inherit "/std/room";

#include "/d/Emerald/defs.h"

void create_room()
{
	set_short("Main road in Leah");
	set_long("   You are on the main street in Leah. The mayor's "+
		"house is just to the east. The street is full of "+
		"people. Beyond the walls of the village you can see "+
		"the tall treetops of the Emerald forest. Far, far in "+
		"the north you can see a large white tower. A sign over "+
		"the door of the building to the west reads: 'Leah Post "+
		"Office'. Directly north is the centre of Leah; "+
		"bustling with people. Walking south will bring you to "+
		"the gates then out into the forest.\n\n");

	add_item("tower", "The tower rises high to the sky. It looks "+
		"dark and gloomy. Perhaps if you took a closer look you "+
		"could see more.\n");
	add_item("forest", "The forest looks dark and you can see no "+
		"way to pass though.\n");
	add_item(({"mayor's house", "house"}),"The Mayor's house looks "+
		"empty. Perhaps you should go in and take a better look.\n");
	add_item(({"Leah", "village"}), "The village of Leah is "+
		"beautiful. Why not explore further to see what wonders "+
		"lie in this small elven community?\n");
	add_item(({"building", "post office"}), "The sign on the "+
		"building proclaims it to be the post office.\n");
	add_item(({"road", "street"}), "The road leads north to the centre "+
		"of Leah and south toward the gates.\n");

	add_exit(VILLAGE_DIR + "centre", "north");
	add_exit(VILLAGE_DIR + "gate", "south");
	add_exit(VILLAGE_DIR + "foyer", "east");
	add_exit(VILLAGE_DIR + "post", "west");
}
