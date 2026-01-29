/*
 *	/d/Gondor/lebennin/road/nr17.c
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

    add_exit(LEB_DIR + "road/nr16",    "northeast", 0, 4);
    add_exit(LEB_DIR + "road/fieldr4", "east",      0, 2);
    add_exit(LEB_DIR + "road/nr18",    "southwest", 0, 4);
   
    add_pelargir("close");
    add_anduin("south");
    add_road(1);
    add_ground();
    add_plain("city");
   
    add_item( ({ "walls", "guards", }), BSN(
        "The walls are too high to scale, and there parapets on top make " +
        "it even impossible to climb into the city over the walls. On the " +
	"battlements on top of the walls, you can see guards walking their " +
        "rounds. You get the impression that they are watching you as " +
        "as you are watching them right now."));
}

