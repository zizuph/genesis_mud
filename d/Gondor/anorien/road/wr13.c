/*
 *	/d/Gondor/anorien/road/wr13.c
 *
 *	Coded 1992 by Elessar.
 *
 *	Modification log:
 *	30-Jan-1997, Olorin:	General revision.
 *      24-Oct-1997, Gorboth:   Closed the path to the south
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
    set_areadesc("grassy field");
    set_areatype(8);
    set_area("northwest");
    set_areaname("Anorien");
    set_land("Gondor");
    set_mountain("");
    set_grass("long, dark green grass");
    set_forest("Firien Forest");
    set_extraline("North and east the long, dark green grass of " +
	"Anorien covers the ground. The famous West Road is seen " +
        "to the west and southeast. The large Firien Forest lies " +
        "to the west and south.");

    set_no_exit_msg(({"southwest","south"}),
        "The dense foliage of the Firien Wood is too thick here for " +
        "you to enter. You will probably have to follow the road from " +
        "here.\n");

    add_exit(ANO_DIR + "road/wr14", "west",      0, 3);
    add_exit(ANO_DIR + "road/wr12", "southeast", 0, 3);
    add_exit(ANO_DIR + "plains/an1w2n","northwest",0,5,1);
    add_exit(ANO_DIR + "plains/an2w2n","north",0,5,1);
    add_exit(ANO_DIR + "plains/an3w2n","northeast",0,5,1);
    add_exit(ANO_DIR + "plains/an3w3n","east",0,5,1);
// I am closing the Ranger school area, since it will never be
// finished, and is very old and very odd.
// - Gorboth
//  add_exit("/d/Gondor/school/path/path1", "south" ,0, 2);
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