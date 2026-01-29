/*
 *	/d/Gondor/anorien/road/rroad4.c
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
    set_extraline("The road continues north and southwest, following "+
    "the great river Anduin's west banks. A large stone wall is visible to the "+
    "west, and far beyond it you spot a tall white tower stretching towards "+
    "the sky.");
    add_item("wall","The wall is forming a wide circle around the Pelennor\n"+
    "Fields outside Minas Tirith.\n");
    add_item("river","The river runs to the east of here, slowly arcing westwards.\n");
    add_item("tower","The tower is a tall and thin pinnacle against the western\n"+
   "horizon. You know that this is the Tower of Guard - the Minas Tirith.\n");
    add_exit(ANO_DIR + "road/rroad5", "north",     0, 2);
    add_exit(ANO_DIR + "road/rroad3", "southwest", 0, 2);
}

