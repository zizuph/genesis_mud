/*
 *	/d/Gondor/ithilien/road/rr4.c
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
    set_extraline("The path is more overgrown here, by briar and eglantine, and "+
        "trailing clematis has drawn a veil over it, making it hard to "+
        "follow. It is clear that it leads north, where the forest has been "+
        "spreading close to the river. South the path shows more clearly, following "+
        "the water's edge down the river. The land climbs to the east, and green "+
        "forests dominate the view. A stream comes out of the forest to the east, "+
        "passing under a small stone bridge which the path crosses here. "+
        "The stream then joins with the mighty river Anduin.");
    add_item( ({ "path", "bank", "riverbank"}), BSN(
        "The path runs north and south here along the riverbank and the " +
        "forest. The riverbank slopes down to the river to the west, the " +
        "last few feet being barren of growths from the varying waterlevel."));
    add_item( ({"river", "anduin", }),
        "The mighty river Anduin flows past west of here, on its way south " +
        "to the ocean.\n");
    add_item(({"forest","forests"}), BSN(
        "The forests of Ithilien are lovely to look upon; a refreshing "+
        "smell of green herbs and fair flowers is brought by the wind. "+
        "The entire view to the east is dominated by the forest."));
    add_item("bridge", BSN("The bridge is clearly very old, with mosses " +
        "growing all over it, and stonecrops blooming from every crack " +
        "in the stones."));
    add_item("stream", BSN("It is a small stream only, with fresh water " +
        "from the great forests of Ithilien. It is obviously headed for " +
        "the River Anduin."));
    add_item(({"herbs","flowers","flora","briar","eglantine","clematis"}),
	BSN("Many kinds of plants and flowers grow in Ithilien, some even "+
        "useful as medical herbs, others just a refreshing smell for "+
        "the travellers in this land, this garden of Gondor."));

    add_exit(ITH_DIR+"road/rr5", "north", 0, 3);
    add_exit(ITH_DIR+"road/rr3", "south", 0, 3);

    BEACH;
    add_prop(OBJ_I_CONTAIN_WATER, 1000000);
}

