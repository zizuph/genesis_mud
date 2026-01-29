inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"

create_room()
{
	set_short("In some shrubs just east of the Old North Road");
	set_long(
		"You are east of the Old North Road, in some shrubs. The path is "+
		"almost completely hidden, but visible for keen eyes. The road leads "+
		"over some plains, with scattered trees and grass. You cannot percieve "+
		"much of your surroundings as the bushes cover your entire view.\n");
	ITEM(({"old north road", "north road", "old road", "road"}), "The Old North "+
		"Road goes all the way north towards Fornost and Annuminas, which lay "+
		"by lake Evendim. The road is also called the greenway, as it has been "+
		"covered with grass and shrubs. You cannot see it from here.\n");
	ITEM("shrubs", "The shrubs is rather thick, and green. It looks almost "+
		"impossible to force your way throug them.\n");
	ITEM("path", "The path seems to go nowhere. However, you think that you "+
		"see some tracks that leads east, deeper into the shrubs. Westwards "+
		"the path seems to go into an area where the bushes is a bit lighter.\n");
	ITEM("plains", "The plains consist mainly of scattered trees and grass.\n");
	add_exit(BREE_DIR +"archet/archet2", "east", 0, 3);
	add_exit(BREE_DIR +"oldroad3", "west", 0, 3);
	set_noshow_obvious_exit(1);
}
 
