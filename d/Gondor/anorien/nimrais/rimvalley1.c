/*
 *	/d/Gondor/anorien/nimrais/rimvalley1.c
 *
 *	Coded by Elessar, 1992
 *
 *	Modification log:
 *	 7-Feb-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    string *herbs;

    set_areatype(1);
    set_areadesc("field");
    set_grass("thick");
    set_area("western");
    set_areaname("Anorien");
    set_land("Gondor");
    set_extraline("The fields of Anorien stretch out to the east, north and "+
    "west. There seems to be a road further north of here. To the south "+
    "you can see the opening of a valley in the White Mountains. Upon "+
    "a hill-top to the southeast you see a beacon-tower.");
    add_item("road","You see a road to the north - it might be the Great West Road.\n");
    add_item(({"beacon","tower"}),"It is the 5th of the northern beacon-towers of Gondor. The beacon is built\n"+
    "upon the hill Rimmon, and was named Min-Rimmon. The beacons are lit\n"+
    "to warn the inhabitants of Gondor and Rohan of invasion or war.\n");
    add_item("valley","It is the Rimmon valley, green and fair, but rumoured to house trolls...\n");

    add_exit(ANO_DIR + "road/wr10",          "north", 0, 2);
    add_exit(ANO_DIR + "nimrais/rimvalley2", "south", 0, 2);

    herbs = HERB_MASTER->query_herbs( ({ "hills", "moderate", }));
    set_up_herbs( ({ ONE_OF_LIST(herbs), ONE_OF_LIST(herbs), 
		     ONE_OF_LIST(herbs),}),
		  ({ }), 3);
}

