inherit "/std/room";

#include "/d/Emerald/defs.h"

void create_room()
{
	object door;

	set_short("Outside tower");
	set_long("   You enter a lovely garden with "+
		"a magnificent white marble tower to the north. The gardens are "+
		"fashioned into beautiful patterns with flowers all around. "+
		"To the south you can see the rest of the town.\n\n");
	
        add_exit(VILLAGE_DIR + "tower", "south");
	add_exit(VILLAGE_DIR + "garden4", "northeast");
	add_exit(VILLAGE_DIR + "garden3", "northwest");

	add_item(({"tower"}), "The tower is solidly built from white marble "+
		   "but you see that there are no cracks in it's gleaming surface "+
		   "as if it were built whole from marble.\n");
	add_item(({"gardens", "patterns"}),"The gardens are arranged with "+
		   "loving care into lovely patterns of beautiful flowers by "+
		   "the tower's owners gardener.\n");
	add_item(({"flowers"}), "The flowers are a mixture of all colours "+
		   "arranged in a nice pattern.\n");

	add_prop(ROOM_I_INSIDE, 0);
	door=clone_object(VILLAGE_DIR + "doors/door_b");
	door->move(this_object());
}
