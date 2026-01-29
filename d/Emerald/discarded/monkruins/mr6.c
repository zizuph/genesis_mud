/*
 * MR6.c 
 * Ruins of Kamesh
 * - Alaron January 1997
 */

#include "/d/Emerald/defs.h"
#include "default.h"

inherit "/std/room";

void
create_room()
{
    set_short("A mist-covered path in a ruined monastery");
    set_long("   The path here is covered by a thin mist. The buildings "+
	     "on either side of the path are ancient, cracked and look "+
	     "to be on the verge of collapsing to the ground. The ruins "+
	     "spread out all around you, displaying a vast landscape of "+
	     "broken, ancient stone structures. To the southwest you can "+
	     "see the dim shadow of a large, square building. The path "+
	     "continues to the north and south from here. A chill wind "+
	     "whips through the holes in the stone walls, creating a "+
	     "soft wailing sound which sends a chill down your spine.\n\n");

    add_prop(ROOM_I_INSIDE, 0);

    add_item( ({"path", "narrow path", "ground", "down"}),
	     "The path beneath you is nothing more than a narrow strip "+
	     "of dirt covered with pebbles, rocks and weeds. At one "+
	     "point this path was a large, wide road which saw frequent "+
	     "traffic. Now it is barely noticeable.\n");

    add_item( ({"mist", "thin mist"}),
	     "The thin mist hangs over the area, creating a dampness that "+
	     "blankets the dirt and grass on the path. It is not quite "+
	     "thick enough to distort your vision. The mist appears to be "+
	     "thicker to the southeast.\n");

    add_item( ({"ruins", "ruined buildings", "ruined monastery",
		"monastery", "structures", "stone structures", "walls",
		"cracks"}),
	     "The ruined buildings are in terrible shape. You notice "+
	     "hundreds of cracks, chips and holes in the walls. None of "+
	     "the buildings have roofs and some are even missing walls.\n");

    add_item( ({"shadow", "building", "square building", 
		"large building", "large square building"}),
	     "The large, square building to the southwest is difficult "+
	     "to see through the thick mist. You can tell, however, that "+
	     "it looks intact, and you can even see a little bit of a "+
	     "roof.\n");

    add_exit(MONKRUIN_DIR + "mr8", "southwest", "@@spooky@@");
    add_exit(MONKRUIN_DIR + "mr7", "south");
    add_exit(MONKRUIN_DIR + "mr5", "north");
}

int
spooky()
{
    write("As you walk along the path toward the large, square building, "+
	  "a sense of fear and trepidation overcomes you. The air here "+
	  "feels thinner and a lot colder ...\n\n");
    return 0;
}

