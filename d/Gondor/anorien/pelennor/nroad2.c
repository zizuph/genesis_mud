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
    set_area("central");
    set_areaname("Pelennor");
    set_land("Gondor");
    set_grass("long, dry, light green");
    set_areatype(8);
    set_areadesc("farmland");
    set_extraline("The road you are on runs through the Fields of Pelennor, "+
	"taking you north towards the north gate of the outer wall, and south "+
	"towards the Great Gate of Minas Tirith, the Tower of Guard. There are "+
	"more fields in all directions.");
    add_exit(PEL_DIR + "nroad3", "north", 0, 2);
    add_exit(PEL_DIR + "nroad1", "south", 0, 2);
}
