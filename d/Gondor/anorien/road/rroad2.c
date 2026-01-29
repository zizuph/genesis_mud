/*
 *	/d/Gondor/anorien/road/rroad2.c
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
    set_areadesc("green, sloping riverbank");
    set_areatype(8);
    set_area("southern");
    set_areaname("Anorien");
    set_land("Gondor");
    set_grass("juicy green");
    set_extraline("The great wall called Rammas Echor goes in a wide circle "+
    "surrounding the Pelennor Fields north of here. To the south and east "+
    "is the great river Anduin, flowing in a slow arc past the grassy fields. "+
    "The road runs alongside the river west and northeast.");
    add_exit(ANO_DIR + "road/rroad3", "northeast", 0, 2);
    add_exit(ANO_DIR + "road/rroad1", "west",      0, 2);
    add_item( ({ "wall", "rammas echor", }), 
	     "The great stone wall forms an immense circle around the " +
	     "Fields of Pelennor.\n");
    add_item( ({ "river", "anduin", }), 
	     "The great river Anduin runs past to the east and south.\n");
}
