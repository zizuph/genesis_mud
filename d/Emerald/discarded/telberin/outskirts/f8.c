/*
 * F8.c
 * Telan Road
 * Road following the forest on the west to Telberin
 */

#include <stdproperties.h>
#include "default.h"

inherit "/std/room";

void
create_room()
{
    set_short("Telan Road");
    set_long("   The road here is wide and well-worn. The span "+
	     "of worn grass and open dirt on the road is wide enough "+
	     "to allow for two carriages to travel comfortably alongside "+
	     "eachother. The landscape expands in all directions in a "+
	     "mass of green. The rolling, soft hills seem to flow away "+
	     "from the road like waves of sand and grass. On the west, "+
	     "the road is bordered by the edge of a tremendous forest. The "+
	     "road itself continues between the forest edge and the soft, "+
	     "green hills to the north and southeast.\n\n");

    add_prop(ROOM_I_INSIDE, 0);

    add_item( ({"road", "down", "ground", "worn grass", "dirt",
		"open dirt"}),
	     "The road here is wide enough for two carriages to travel "+
	     "alongside eachother comfortably. Judging from the subtle "+
	     "ruts of worn grass and packed dirt on either side of the "+
	     "road, you guess that this happens quite often. The road "+
	     "looks very well travelled.\n");

    add_item( ({"landscape", "hills", "soft hills", "green hills",
		"rolling hills"}),
	     "The soft, rolling hills seem to flow up and down out of "+
	     "the ground in a wavelike drift, heading away from the road.\n");

    add_item( ({"forest", "west", "trees", "forest edge", "edge", "woods",
		"wood", "tremendous forest"}),
	     "The enormous forest sprawls out to encompass the entire "+
	     "landscape on the west side of the road. The trees are "+
	     "incredibly tall, and full of beautiful, thick green life.\n");

    add_exit(OUT_DIR + "f12", "southeast");
    add_exit(OUT_DIR + "f3", "north");
}
