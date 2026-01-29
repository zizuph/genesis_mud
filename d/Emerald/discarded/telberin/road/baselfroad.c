/*
 * BASELFROAD.c
 * Base Forest Road leading from the Telberin Road to Leah
 * - Alaron January 1997
 */

#include "/d/Emerald/defs.h"

inherit "/std/room";

void create_lforest();

void
create_room()
{
    set_short("A forest road");
    set_long("This is a forest. Re-Describe me ASAP.\n\n");

    add_prop(ROOM_I_INSIDE, 0);

    add_item(({"trees", "tree", "forest", "woods", "wood"}),
	     "The forest expands on both sides of the narrow road. The "+
	     "huge tops of the trees seem to reach all the way to the "+
	     "clouds. The height of the trees and narrowness of the road "+
	     "creates plenty of shade for the path.\n");

    add_item( ({"down", "ground", "road", "dirt", "path"}),
	     "The dirt road is narrow, but very well packed from obvious "+
	     "heavy traffic in both directions. You stop to wonder what "+
	     "people do when more than one carriage attempts to use this "+
	     "road at the same time.\n");

    add_item( ({"up", "sky", "clouds", "blue sky", "cloud"}),
	     "The sky is filled with clouds.\n");

}

void
create_lforest()
{
}
