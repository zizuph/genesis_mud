/*
 *	/d/Gondor/anorien/pelennor/nroad1.c
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
    set_area("northern");
    set_areaname("Pelennor");
    set_land("Gondor");
    set_grass("long, dry, light green");
    set_areatype(8);
    set_areadesc("grassy field");
    set_extraline("The road runs south across the northern part of " +
        "the Fields of Pelennor and north to the north gate of the " +
        "Rammas Echor, the outer wall that surrounds the fields around " +
        "Minas Tirith.");
    add_exit(PEL_DIR + "ningate","north", 0, 2);
    add_exit(PEL_DIR + "nroad2","south",  0, 2);
}
