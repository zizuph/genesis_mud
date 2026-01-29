/*
 *	/d/Gondor/anorien/pelennor/neroad1.c
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
    set_area("central");
    set_areaname("Pelennor");
    set_land("Gondor");
    set_areatype(8);
    set_grass("long, soft, light green");
    set_areadesc("field");
    set_extraline("The road you are on continues northeast across the fields of "+
	  "Pelennor, and southwest to the Great Gate of Minas Tirith. You can "+
	  "spot the White Tower rising up from the City to the west.");
    add_exit(PEL_DIR + "neroad2",  "northeast", 0, 2);
    add_exit(PEL_DIR + "citygate", "southwest", 0, 2);
}
