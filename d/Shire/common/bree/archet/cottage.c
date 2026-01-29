#include "defs.h"
inherit SHIRE_DIR +"room";

create_room()
{
	set_short("Outside a small cottage");
	set_long(
		"You re standing in a garden outside a cottage. The entrance is"+
		"just east of here, and a road leads south, through the garden and "+
		"to the backyard of the house. The house has a small window in the "+
		"front door, and is painted red. A large saw can be seen south of "+
		"here, and a lot of cut wood. Maybe it is a timberman who live in "+
		"this cute house?\n");
	add_exit(ARCHET_DIR +"inside", "enter", 0);
	add_exit(ARCHET_DIR +"archet16", "west", 0);
	add_exit(ARCHET_DIR +"backyard", "south", 0);
	ITEM("house", "The house is made out of solid wood, oak it seems. It is "+
		"roughly build, but looks stern and offer good shelter.\n");
}

