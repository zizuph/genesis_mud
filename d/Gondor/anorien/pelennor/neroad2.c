/*
 *	/d/Gondor/anorien/pelennor/neroad2.c
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
    set_area("north-eastern");
    set_areaname("Pelennor");
    set_land("Gondor");
    set_areatype(8);
    set_grass("long, light green");
    set_areadesc("field");
    set_extraline("The road you are on leads northeast towards Osgiliath, "+
	"and southwest towards Minas Tirith. You can spot the White Tower "+
	"in the distance to the southwest, while there are fields around you "+
	"in all directions.");
    add_exit(PEL_DIR + "neroad3", "northeast", 0, 2);
    add_exit(PEL_DIR + "neroad1", "southwest", 0, 2);
}
