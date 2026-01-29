/*
 * MR7.c
 * Ruins of Kamesh
 * - Alaron January 1997
 */

#include "/d/Emerald/defs.h"
#include "default.h"

inherit "/std/room";

void
create_room()
{
    set_short("A dead-end path through the ruins of a monastery");
    set_long("   You are standing at the end of the path. The path "+
	     "leads off into the ruins to the north, where it is "+
	     "quickly swallowed by the constantly hovering cloud of "+
	     "fog and moisture. There are no ruined buildings in the "+
	     "vicinity, only a few scattered trees and patches of "+
	     "high bushes. All of the crumbling buildings are to the north "+
	     "and east of here.\n\n");

    add_prop(ROOM_I_INSIDE, 0);

    add_item( ({"path", "road", "ground", "dirt", "down"}),
	     "The path is not much more than a strip of dirt "+
	     "covered by pebbles and bushes. It gets slightly wider "+
	     "to the north, but not by much. The path is nothing "+
	     "compared to the size it must have been before ruin "+
	     "came to the monastery.\n");

    add_item( ({"fog", "moisture", "cloud", "mist"}),
	     "The path is quickly swallowed up by the mist to the "+
	     "north. You wonder what could possibly keep this area "+
	     "under so much moisture that the mist and fog never "+
	     "seem to burn off.\n");

    add_item( ({"trees", "bushes"}),
	     "The trees and bushes are all very heavy with leaves "+
	     "and seem to be growing rampantly. Their dark green color "+
	     "contrasts starkly with the dull, lifeless gray that the "+
	     "mist to the north generates.\n");

    add_exit(MONKRUIN_DIR + "mr6", "north");
}

    
