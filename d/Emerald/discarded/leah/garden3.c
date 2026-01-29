inherit "/std/room";

#include "/d/Emerald/defs.h"

void create_room()
{

        set_short("Outside tower");
        set_long("   You are standing in some gardens to the "+
		"west of a pure white marble tower. The gardens are "+
		"exquisitely kept, and are beautifully grown. There "+
		"is a carefully pruned hedge arrangement here.\n\n");

        add_exit(VILLAGE_DIR + "garden1", "southeast",);
        add_exit(VILLAGE_DIR + "garden2", "northeast",);

        add_item(({"tower"}), "The tower is solidly built from white marble; "+
                   "you see that there are no cracks in its gleaming surface "+
                   "as if it were built from one huge slab.\n");
        add_item(({"gardens", "patterns"}),"The gardens are arranged with "+
                   "care into lovely patterns of beautiful flowers by "+
                   "the tower's owner's gardener.\n");
        add_item(({"flowers"}), "The flowers are a mixture of all colours "+
                   "arranged in a nice pattern.\n");
	add_item(({"arrangement","hedge"}),"The hedge has been "+
		   "shaped into a maze, but is not open at the moment.\n");
        add_prop(ROOM_I_INSIDE, 0);
}
