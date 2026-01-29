/*
 *	/d/Gondor/anorien/pelennor/neroad3.c
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
    set_grass("long, soft, light green");
    set_areadesc("field of agriculture");
    set_extraline("The dusty road you are on runs northeast, where it "+
	"meets the north-eastern gate of the Rammas Echor. Southwest will "+
	"take you across the fields of Pelennor, towards Minas Tirith. "+
	"There are more fields in all other directions.");
    add_exit(PEL_DIR + "neingate", "northeast", 0, 2);
    add_exit(PEL_DIR + "neroad2",  "southwest", 0, 2);
}
