/*
 * P1.c
 * Fork in Telan Road.
 * - Alaron January 1997
 */

#include "/d/Emerald/defs.h"
#include "default.h"

inherit "/std/room";

void
create_room()
{
    set_short("Fork in a forest road");
    set_long("   You are standing on a road leading through a "+
	     "forest. Green surrounds you in all shapes and forms. "+
	     "Huge, towering trees of almost unreal height bathe "+
	     "the path in soft, comfortable shadow. Bushes and grass "+
	     "run rampant along the sides of the dirt road and thick "+
	     "green vines hang from some of the trees on the woodline. "+
	     "The dirt road continues deeper into the giant forest as "+
	     "it expands to the north, as the forest spreads and thins out "+
	     "around the path to the south. You can hear the sounds of "+
	     "several varieties of woodland animals coming from within "+
	     "the wood. The sounds are comforting and welcoming. The fork "+
	     "in the forest road provides three choices for direction, "+
            "north, northwest, and southwest. Peering down the fork "+
            "leading northwest, you think you can make out the faint "+
            "glimmer of a lake.\n\n");
    
    add_item(({"lake", "glimmer"}),
             "You think you see the glimmer of reflected light off of the "+
             "surface of a lake, but you can't be sure from this distance.\n");
    add_item( ({"road", "down", "ground", "dirt", "path", "dirt road"}),
	     "The hard-packed, dirt road beneath you apparently sees "+
	     "quite a bit of traffic. The dirt and grass along the road "+
	     "is packed to a solid base, with ruts on either side of the "+
	     "road indicating heavy wagon or carriage traffic.\n");

    add_item( ({"trees", "forest", "forests", "wood", "woods", "treetops"}),
	     "The trees tower above you on either side, forcing you to "+
	     "bend back and crane your neck to see the treetops which "+
	     "bathe the road in shade.\n");

    add_item( ({"bushes", "grass"}),
	     "Bushes and grass run rampant all along the side of the "+
	     "road between the edge of the packed dirt and the beginning "+
	     "of the treeline.\n");

    add_item("fork",
	     "The fork in the road here leads off in three directions. A "+
	     "path branches off to the north, while the main road "+
	     "continues northwest and southwest.\n");

    add_exit(LROAD_DIR + "road01", "northwest");
    add_exit(OUT_DIR + "f5", "southwest");
    add_exit(OUT_DIR + "p2", "north");
}

		
