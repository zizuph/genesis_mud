/*
 * P2.c
 * This is a path entrance into the farm.
 */

#include "/d/Emerald/defs.h"
#include "default.h"

inherit "/std/room";

void
create_room()
{
   set_short("Forest path");
   set_long("   You are standing on a narrow, forest path. The path "+
	    "is dwarfed on three sides by towering, giant trees which "+
	    "cover the entire path in shade, creating more of a passage "+
	    "or tunnel feeling to the area. An even smaller path leads "+
	    "into a clearing beyond a section of trees where you can "+
	    "see a barn in the distance. The path leads south of here "+
	    "where it joins a larger, well-travelled road.\n\n");

   add_item( ({"path", "narrow path", "ground", "dirt", "dirt path"}),
	    "The path is a narrow stretch of flat, trampled grass and "+
	    "dirt between two giant rows of towering trees. A smaller "+
	    "path leads off to a clearing to the east. This path joins "+
	    "with a larger road to the south.\n");

   add_item( ({"forest", "forests", "woods", "wood", "trees", "tree"}),
	    "The trees surround the path on three sides, dwarfing it "+
	    "by their immense size and hiding it in shade beneath their "+
	    "sprawling, leafy tops.\n");

   add_item( ({"clearing", "barn"}),
	    "Off in the distance to the east, there is a clearing "+
	    "in the middle of the forest. It looks very quiet and "+
	    "serene. Peering through the trees you can make out a "+
	    "large wooden barn and a stretch of old, wood-post "+
	    "fencing.\n");

   add_exit(OUT_DIR + "p1", "south");
    add_exit("/d/Emerald/farm/froad1", "east", "@@noway");
}

int
noway()
{
    write("As you start heading toward the farm, you notice that "+
          "there is a fence surrounding the property, which is "+
          "currently closed and locked. You decide against "+
          "trespassing.\n");
    return 1;
}
