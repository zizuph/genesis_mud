/*
 *	/d/Gondor/lebennin/road/nr15.c
 *
 *
 *	Revision history:
 *	Updated code - 05/06/96 - By Arren
 *	 3-Feb-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/lebennin/road/road.c";

#include "/d/Gondor/defs.h"

#define MAX_TRAV 3

static object *Trav = allocate(MAX_TRAV);

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

    add_exit(LEB_DIR + "road/nr14", "northeast", 0, 4);
    add_exit(LEB_DIR + "road/nr16", "southwest", 0, 4);
   
    add_pelargir("far");
    add_anduin("south");
    add_road(1);
    add_ground();
    add_plain("forest");

    reset_room();
}

public void
reset_room()
{
    clone_npcs(Trav, LEB_DIR + "npc/traveller", 10.0 + rnd() * 20.0, 
	       LEB_DIR + "road/");
}
