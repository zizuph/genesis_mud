inherit "/std/room";

#include "/d/Emerald/defs.h"

void create_room()
{

	set_short("Dining room");
	set_long("   You are in the dining room of the hotel"+
		"Everything about this room indicates that you are  "+
		"now living in luxury. In the centre of the "+
		"room there is a giant dining table, and outside the "+
		"windows you can see the forest all around you. On "+
		"the table are several menu's \n\n");

	add_item(({"table", "chairs"}), "A large polished oak table "+
		"with eight chairs neatly arranged around it.\n");
	add_item(({"window", "windows", }), "The window gives "+
		"a fine view of the dense forest outside the hotel.\n");
	add_item(({"outside", "forest"}), "The forest is very dense "+
		"with oaks, elms, and other large deciduous trees.\n");
	add_item("menu", "Perhaps you should read it.\n");

	add_prop(ROOM_I_INSIDE, 1);

	add_exit(VILLAGE_DIR + "hotel/kitchen", "south");
	add_exit(VILLAGE_DIR + "hotel/parlor", "east");
}
