/*
 *	/d/Gondor/lebennin/road/nr16.c
 *
 *	Modification log:
 *	 3-Feb-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/lebennin/road/road.c";

#include "/d/Gondor/defs.h"

public void
create_road()
{
    set_area("southern");
    set_areaname("Lebennin");
    set_land("Gondor");
    set_areatype(8);
    set_areadesc("great plain");
    set_grass("green");
    set_extraline("The road runs in a long straight line across " +
        "the wide plain of southern Lebennin towards Pelargir upon " +
        "Anduin. Green fields lie to both sides, and in the east " +
        "shines the wide blue band of the Anduin.");

    add_exit(LEB_DIR + "road/nr15", "northeast", 0, 4);
    add_exit(LEB_DIR + "road/nr17", "southwest", 0, 4);
   
    add_pelargir("medium");
    add_anduin("south");
    add_road(1);
    add_ground();
    add_plain("city");
}
