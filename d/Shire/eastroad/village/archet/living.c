#include "defs.h"
inherit SHIRE_DIR +"room";

create_room()
{
	set_short("In the living room");
	set_long(
		"You are standing in the living room of the cottage, the room "+
		"which appearently most time is spent. Here there is a fireplace "+
		"set up against the western wall, with a huge painting above. "+
		"A door leads east, into what seems to be the kitchen. A large "+
		"couch is set against the northern wall, with a long table infront. "+
		"A deep, skin chair is set infront of the table, and some shelves "+
		"which seem to contain books and other precious items stand towards "+
		"the southern wall, just beside the door opening. South a door leads "+
		"out of here, and into a hall.\n");
	add_exit(ARCHET_DIR +"kitchen", "east", 0);
	add_exit(ARCHET_DIR +"inside", "south", 0);
	ITEM("not much yet", "There is not much here yet, but more is coming!\n");
}

