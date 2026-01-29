/*
 *	/d/Gondor/anorien/road/rroad1.c
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
    set_grass("long, green");
    set_extraline("The river Anduin slowly flows by to the south of here in a "+
    "wide curve around the Pelennor Fields. The walls of the Rammas Echor "+
    "are to the north. Further southwest and south you see the warehouses "+
    "of Harlond, the harbour of Minas Tirith. The road continues east and southwest.");
    add_exit(ANO_DIR + "road/rroad2", "east",      0, 2);
    add_exit(PEL_DIR + "harlond",     "southwest", 0, 2);
}

string
query_dir_to_gate()
{
    return "southwest";
}

