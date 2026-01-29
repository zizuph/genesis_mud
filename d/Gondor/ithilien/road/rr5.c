/*
 *	/d/Gondor/ithilien/road/rr5.c
 *
 *	Coded 1993 by Elessar.
 *
 *	Modification log:
 *	 1-Feb-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areatype(0);
    set_areadesc("path along the east bank of the Anduin");
    set_area("northern");
    set_areaname("the forests");
    set_land("Ithilien");
    set_treetype("cypress");
    set_extraline("The path runs north and south between the river and the "+
        "green forests of North Ithilien. A pleasant smell of flowers and plants "+
        "is ever present as you walk along. The forest dominates the view to the "+
        "east, covering most of the sloping hillsides and ridges in the lands "+
        "that rise towards dark mountains in the east horizon. "+
        "To the west the mighty River Anduin flows quietly past from the "+
        "north towards the south.");
    add_item("path","The path runs north and south here along the river and the\n"+
    "forest. It does not look as if it is used very often.\n");
    add_item(({"river","anduin"}),"The mighty river Anduin flows past west of here, on\n"+
    "its way south to the ocean.\n");
    add_item("forest","The forests of Ithilien are lovely to look upon; a refreshing\n"+
    "smell of green herbs and fair flowers is brought by the wind.\n"+
    "The entire view to the east is dominated by the forest.\n");

    add_exit(ITH_DIR + "road/rr6", "north", 0, 3);
    add_exit(ITH_DIR + "road/rr4", "south", 0, 3);
}

