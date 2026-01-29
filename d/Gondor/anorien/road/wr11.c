/*
 *	/d/Gondor/anorien/road/wr10.c
 *
 *	Coded 1992 by Elessar.
 *
 *	Modification log:
 *	30-Jan-1997, Olorin:	General revision.
 *
 *  Added exits into Anorien plains. 
 *  Varian 2016
 */

#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areadesc("green, grassy field");
    set_areatype(8);
    set_area("western");
    set_areaname("Anorien");
    set_land("Gondor");
    set_mountain("Ered Nimrais, the White Mountains");
    set_grass("soft, green grass");

    add_exit(ANO_DIR + "road/wr10", "east", 0, 3);
    add_exit(ANO_DIR + "road/wr12", "west", 0, 3);
    add_exit(ANO_DIR + "plains/an3w3n","northwest",0,5,1);
    add_exit(ANO_DIR + "plains/an4w3n","north",0,5,1);
    add_exit(ANO_DIR + "plains/an5w3n","northeast",0,5,1);

    set_extraline("The road continues west and east, running just " +
        "north of the Ered Nimrais, the White Mountains, which cover " +
	    "the southern horizon. North the grass-covered fields of " +
        "Anorien stretch as far as one can see.");

    set_no_exit_msg(({"southwest","south","southeast"}),
        "The broken foothills of the White Mountains are too difficult " +
        "for you to climb from here. You will have to find a path of " +
        "some sort to continue in that direction.\n");
}

/*
 This was used while the plains were under construction. Now open
 Varian - August 2016

int
block()
{
    if (this_player()->query_wiz_level()) return 0;

    write("You should be able to enter the plains of Anorien soon!\n");
    return 1;
}

*/