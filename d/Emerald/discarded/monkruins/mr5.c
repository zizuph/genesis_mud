/*
 * MR5.c
 * Ruins of Kamesh
 * - Alaron January 1997
 */

#include "/d/Emerald/defs.h"
#include "default.h"

inherit "/std/room";

void
create_room()
{
    set_short("A narrow path through the ruins of a monastery");
    set_long("   You are standing on a narrow, weed-covered path "+
	     "which winds its way through the massive stone ruins of "+
	     "an ancient monastery. The buildings would have been massive "+
	     "in their prime, centuries ago. Now they are nothing more "+
	     "than broken relics with cracks in their walls and open air "+
	     "for their roofs. The path continues to wander through the "+
	     "ruined place of worship and serenity to the east, southeast, "+
	     "and south. A thick fog hangs over the ruins to the east, but "+
	     "thins out to a fine mist south of here.\n\n");

    add_prop(ROOM_I_INSIDE, 0);

    add_item( ({"path", "narrow path", "dirt", "ground", "down"}),
	     "The path is narrow and not much more than a patch of "+
	     "dirt covered with pebbles and weeds.\n");

    add_item( ({"ruins", "monastery", "buildings", "ruined buildings",
		"walls", "cracks"}),
	     "The ruins of the monastery tower over the narrow path. The "+
	     "cracked, crumbling walls of the buildings look like they "+
	     "could collapse at any moment. None of the ancient buildings "+
	     "have any roofs, and most of them are missing some of their "+
	     "walls, appearing to be nothing more than a few rectangles of "+
	     "stone jutting out of the foundation.\n");

    add_item( ({"fog", "thick fog"}),
	     "There is a thick fog which hangs over the ruins to the east, "+
	     "and seems to thin out into a fine mist to the south of "+
	     "here.\n");

    add_exit(MONKRUIN_DIR + "mr6", "south");
    add_exit(MONKRUIN_DIR + "coast8", "east");
    add_exit(MONKRUIN_DIR + "mr4", "southeast");
    
}
