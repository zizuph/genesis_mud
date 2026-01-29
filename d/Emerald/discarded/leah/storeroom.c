inherit "/std/room";

#include "/d/Emerald/defs.h"

void
create_room()
{
	add_prop(ROOM_I_INSIDE, 1);
	set_short("Storage Room");
	set_long("   You are in the storage room of the elven "+
		"house. Along three walls there are floor-to-ceiling "+
		"shelves filled to overflowing with food and "+
		"commodities. Squeezed in the northwest corner is a "+
		"small, but sturdy looking ladder.\n\n");

	add_item(({"ladder", "corner"}), "It looks quite solid. However, "+
		"it is bolted to the floor.\n");
	add_item(({"shelves","shelf", "walls", "floor", "ceiling"}),"The "+
		"shelves are crammed full of various ingredients.\n");
	add_item(({"food", "commodities"}), "You see all manner of "+
		"foodstuffs on the shelves.\n");

	add_exit(VILLAGE_DIR + "attic", "up", 0);
	add_exit(VILLAGE_DIR + "kitchen", "south", 0);
}
