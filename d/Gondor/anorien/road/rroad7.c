/*
 *	/d/Gondor/anorien/road/rroad7.c
 *
 *	Coded by Elessar.
 *
 *	Modification log:
 *	30-Jan-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areadesc("grassy field");
    set_areatype(8);
    set_area("southeastern");
    set_areaname("Anorien");
    set_land("Gondor");
    set_extraline("The stone wall to the west arcs further away from you, and you "+
    "notice a line of trees leading northeast from the wall. Further north is "+
    "a ruined city - stone buildings torn down by weather and warfare. The "+
    "road runs straight towards it, and continues along the river southwards. "+
    "Across the river Anduin to the east you see green forests.");
    add_exit(ANO_DIR + "road/rroad8", "north", 0, 2);
    add_exit(ANO_DIR + "road/rroad6", "south", 0, 2);
    add_item("trees","The trees are placed in a perfect line, and you suspect that\n"+
	     "they are lining a road.\n");
    add_item("city","The ruined city is Osgiliath, destroyed first by civil war,\n"+
	     "then by orc-raids.\n");
    add_item("wall","The great stone wall known as the Rammas Echor arcs away\n"+
	     "from you to the west. A line of trees lead right up to it.\n");
}
