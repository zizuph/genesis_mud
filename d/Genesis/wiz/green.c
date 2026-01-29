#pragma save_binary

#include <stdproperties.h>
#include "default.h"

create_room() 
{
	set_short("The center of wizards island");
	set_long(
		"You stand in the middle of the wizards island.\n" +
		"This island was built before time by a wizard who valued his privacy!\n" +
		"You stand on a green grass lawn.\n" +
		"There are some footprints in the grass.\n" +
		"On the island you will find education, entertainment and rest.\n" +
		"To the south you can see the wizards club house.\n" +
         "To the west you can see the wizards guildhall.\n" +
		"To the north and east you see the park.\n" +
		"Further to the north you can see a tremendous tower rising towards the sky!\n" +
		"Leading down is a staircase.\n"
	);
	add_item("footprints", "The footprints have been caused by wizards standing here idle too long.\n");
	add_exit(THIS_DIR + "entrance", "south");
	add_exit(THIS_DIR + "park_n", "north");
	add_exit(THIS_DIR + "stairtop", "down", "@@down_msg");
	add_exit(THIS_DIR + "park_e", "east");
	add_exit(THIS_DIR + "guildhall", "west", 0);
	add_default_exits();
	change_prop(ROOM_I_LIGHT, 10);
}

down_msg()
{
	write("You walk down endless stairs without end.\n" +
		"You come out on the underside of the island that looks\n" +
		"like its floating in midair!\n" +
		"The stairs goes on downwards.\n"
	);
	return 0;
}