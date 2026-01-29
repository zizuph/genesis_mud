/*
 * F4.c
 * Telan Road, road to telberin.
 */

#include "/d/Emerald/defs.h"
#include "default.h"

inherit "/std/room";

void
create_room()
{
    set_short("Telan Road");
    set_long("   You are standing on a wide, well-travelled road. The road "+
	     "is a hard-packed dirt and grass separator between the immense "+
	     "forest to the west and the rolling, soft green hills. Woods "+
	     "far off to the east expand to near forest-like proportions "+
	     "further to the north. The road continues on its winding course "+
	     "from here to the northeast and southwest. The road becomes "+
	     "shaded and more secluded as the woods on both sides seem to "+
	     "close in upon it further north.\n\n");

    add_item( ({"road", "down", "ground", "dirt", "grass"}),
	     "The road here is hard-packed and made of dirt and grass. "+
	     "Judging from the ruts on either side of the road you guess "+
	     "that the road gets frequent, and more than likely heavy, "+
	     "wagon and carriage traffic.\n");

    add_item( ({"forest", "west", "west forest", "immense forest"}),
	     "The forest on the west side of the road is immense, the tips "+
	     "of the trees seem to reach out and touch the clouds.\n");

    add_item( ({"wood", "woods", "east forest", "east"}),
	     "The woods on the east side of the road grow and expand "+
	     "as you scan from south to north. Further north both "+
	     "forests on either sides of the road seem to close in on it, "+
	     "shading it underneath the treetops.\n");

    add_item( ({"hills", "rolling hills", "soft hills", "rolling soft hills",
		"green hills", "soft green hills"}),
	     "The hills and plains roll off to the east side, their crests "+
	     "creating the illusion of wavelike motion from hill to hill. "+
	     "Beyond the hills the woods grow as the road continues north.\n");

    add_exit(OUT_DIR + "f5", "northeast");
    add_exit(OUT_DIR + "f3", "southwest");
}
