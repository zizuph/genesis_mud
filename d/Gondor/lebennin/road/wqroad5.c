/*
 *	/d/Gondor/lebennin/road/wqroad5.c
 *
 *	Coded by Mayhem.
 *
 *	Modification log:
 *	 5-Feb-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areadesc("rolling foothills");
    set_areatype(8);
    set_area("northeastern");
    set_areaname("Lebennin");
    set_land("Gondor");
    set_grass("tangled, dark green");
    set_extraline("Green grasslands stretch out south of here, but around you " +
      "the ground becomes less overgrown and rockier. To both sides of the " +
      "path the foothills of the White Mountains begin to rise. The path continues " +
      "further into the mountains to the north.");
    add_exit(LEB_DIR + "road/wqroad6",  "north",     0, 3);
    add_exit(LEB_DIR + "road/wqfield5", "northeast", 0, 2);
    add_exit(LEB_DIR + "road/wqroad4",  "south",     0, 3);
    add_item(({"peaks","peak","white mountains","ered nimrais","mountains","mountain"}),
    BSN("Some of the peaks of the Ered Nimrais are visible from here, "+
     "others are hidden behind the closer foothills rising to the sides of the path."));
    add_item("grass","Some grass is growing on the rocky ground beside the path.\n");
    add_item(({"hill","hills","foothills"}), 
      "The first foothills of the White Mountains are rising to both sides of the " +
      "path.\n");
    add_item(({"road","path"}), BSN(
      "More of a path than a road, it is winding its way through the hills " +
      "northwards into the mountains."));
    add_item("ground","The ground here is dry and rocky.\n");
}

string 
short_desc()
{
    return "A road through " +areadesc + " in the " + area + " parts of " + areaname; 
}
