/*
 *	/d/Gondor/anorien/pelennor/sroad1.c
 *
 *	Coded by Elessar.
 *
 *	Modification log:
 *	30-Jan-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

public void
create_area_room() 
{
    set_area("southern");
    set_areaname("Pelennor");
    set_land("Gondor");
    set_areatype(8);
    set_areadesc("field");
    set_grass("light green, juicy");
    add_exit(PEL_DIR + "citygate", "north", 0, 2);
    add_exit(PEL_DIR + "singate",  "south", 0, 2);
    set_extraline("To the north you see the Great Gate of Minas Tirith, "+
	"the gate that leads through the First Wall, and which all must pass "+
	"to enter the City. South is the southern gate of the Rammas Echor, "+
	"the out-wall which surrounds the fields of Pelennor. Both east and "+
	"west, you see the fields stretch out.");
}
