/*
 * F3.c
 * Telan Road, road to telberin.
 * - Alaron January 1997
 */

#include "/d/Emerald/defs.h"
#include "default.h"

inherit "/std/room";

object tracker;

void reset_room();

void
create_room()
{
    set_short("Telan Road");
    set_long("   You are standing on a wide, well-travelled road. The "+
	     "road winds around the edge of an enormous forest on its "+
	     "west side, and soft, rolling green hills on the east side. "+
	     "A small section of woods far off to the east begins to expand "+
	     "to near forest proportions as it parallels the road heading "+
	     "northeast. The forest on the west side of the road is "+
	     "immense and filled with tall, thick trees which must be "+
	     "centuries old.\n\n");

    add_item( ({"forest", "woods", "wood", "west"}),
	     "The forest bordering the west side of the road is "+
	     "enormous. The tops of the trees seem to reach up and "+
	     "touch the clouds.\n");

    add_item( ({"road", "path", "ground", "down"}),
	     "The road here is well-travelled and hard-packed. It looks "+
	     "like this road sees quite a lot of traffic from carriages, "+
	     "horses and travellers alike.\n");
    
    add_item( ({"sky", "up"}),
	     "You peer up at the sky in awe of the clouds.\n");

    add_exit(OUT_DIR + "f8", "south");
    add_exit(OUT_DIR + "f4", "northeast");

    set_alarm(1.0, 0.0, reset_room);
}

void
reset_room()
{
    if(tracker)
        return;
    else
        tracker = clone_object(NPC_DIR + "tracker");

    tracker->arm_me();
    tracker->move_living("into a room", TO);
}

