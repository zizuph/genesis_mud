/*
 * F5.c
 * Road to Telberin
 * Telan Road
 * Alaron January 1997
 */

#include "/d/Emerald/defs.h"
#include "default.h"

inherit "/std/room";


void
create_room()
{
    set_short("Telan Road");
    set_long("   Standing on a wide, well-travelled road, you survey "+
	     "the area around you. Trees seem to come at the road from "+
	     "both sides. The forest on the west side of the road seems to "+
	     "push in at the road, the treetops leaning over the packed "+
	     "dirt and grass, providing plenty of shade. The woods on the "+
	     "east side of the road are smaller, and pushed back a little "+
	     "from the road. Further north, both sides of the road are "+
	     "shaded by the treetops of forest edges. The road continues "+
	     "on to the southwest and to a fork northeast.\n\n");

    add_item(({"road", "ground", "down", "dirt", "packed dirt", "grass"}),
	     "The hard, packed dirt road beneath your feet seems "+
	     "to be very well travelled. The ruts on either side of the "+
	     "road also indicate heavy wagon or carriage traffic.\n");

    add_item(({"forests", "forest", "woods", "wood", "trees", "treetops",
	       "forest edges", "forest edge", "edge"}),
	     "The forests seem to be converging on the road. The east woods "+
	     "begin as a small cluster of trees to the southeast and grow "+
	     "rapidly outward from there, trying to engulf the road. The "+
	     "west side of the road is dwarfed by towering trees. The "+
	     "treetops hang overtop of the road, providing shade.\n");
    
    add_exit(OUT_DIR + "f4", "southwest");
    add_exit(OUT_DIR + "p1", "northeast");
   
}
