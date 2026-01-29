inherit "/std/room";

#include "/d/Emerald/defs.h"

void create_room()
{
	add_prop(ROOM_I_INSIDE, 1);
	set_short("Dining room");
	set_long("   You are in the dining room of the elven "+
		"house. Everything about this room indicates that a "+
		"very wealthy man has lived here. In the centre of the "+
		"room there is a giant dining table, and outside the "+
		"windows you can see the forest all around you.\n\n");

	add_item(({"table", "chairs"}), "A large polished oak table "+
		"with six chairs neatly arranged around it.\n");
	add_item(({"window", "windows", }), "The window gives "+
		"a fine view of the dense forest outside the village.\n");
	add_item(({"outside", "forest"}), "The forest is very dense "+
		"with oaks, elms, and other large deciduous trees.\n");

	add_exit(VILLAGE_DIR + "kitchen", "west");
	add_exit(VILLAGE_DIR + "livingroom", "south");
}
