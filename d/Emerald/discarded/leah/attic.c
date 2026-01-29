inherit "/std/room";

#include "/d/Emerald/defs.h"

void create_room()
{
	add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_LIGHT, 0);
        set_short("Attic");
	set_long("   You are in the dusty attic of an elven house. "+
		"The windows are boarded up, letting in very small "+
		"streaks of dusty sunlight. You stoop as you walk, "+
		"avoiding cobwebs. All kinds of old furniture and "+
		"strange things lie scattered around the floor.\n\n");

	add_item(({"windows", "boards"}), "Boards cover the windows "+
		"blocking out all but a minimal amount of light.\n");
	add_item(({"light", "sunlight", "streaks"}), "The few streaks "+
		"of light coming in through the windows only serve to "+
		"make it harder to see.\n");
	add_item(({"cobwebs"}), "Cobwebs hang from the ceiling and cover "+
		"everything in this dusty room.\n");
	add_item(({"furniture", "strange things", "floor"}), "You "+
		"recognize some of these items as old pieces of "+
		"furniture, but some are not so easy to identify.\n");

	add_exit(VILLAGE_DIR + "storeroom", "down", 0);
}
