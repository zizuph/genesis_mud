/*
 *	/d/Gondor/ithilien/road/rr1.c
 *
 *	Coded 1993 by Elessar.
 *
 *	Modification log:
 *	28-Jan-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areatype(0);
    set_areadesc("path along the forest's edge");
    set_area("northern");
    set_areaname("the forests");
    set_land("Ithilien");
    set_extraline("The path runs north and south between the river and the "+
    "forest. The ruins of East Osgiliath can be spotted behind the few trees, "+
    "and beyond the Anduin you see the rest of it. The rather dense "+
    "undergrowth along the river forces you to follow the old path.");
    add_item("ruins", BSN("They are ruins of ancient buildings of "
        + "stone, a city built upon the river Anduin ages ago, and "
        + "which was destroyed during wars that occurred centuries "
        + "ago. Osgiliath was once the capital of Gondor, now but a "
        + "thorn in the history of the Gondorian people."));
    add_item("river","The mighty river Anduin flows past west of here, on "+
	     "its way south to the ocean.\n");
    add_item("forest", BSN("The forests of Ithilien are lovely to "
        + "look upon; a refreshing smell of green herbs and fair "
        + "flowers is brought by the wind. The entire view to the "
        + "east is obscured by the forest."));

    add_exit(ITH_DIR + "road/rr2",        "north", 0, 2);
    add_exit(ITH_DIR + "osgiliath/nosg1", "south", 0, 2);
}

