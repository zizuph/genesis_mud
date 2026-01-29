/*
 *	/d/Gondor/anorien/road/wr9.c
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
    set_areadesc("green, long-grassed field");
    set_areatype(8);
    set_area("western");
    set_areaname("Anorien");
    set_land("Gondor");
    set_mountain("Ered Nimrais");
    set_grass("light green, dry grass");
    set_extraline("Following the road, you see a large forest to the southeast, " +
        "while there are plains both north and west. A little further south " +
        "however, you see the Ered Nimrais rising steeply above the rather " +
        "flat terrain. The road continues northwest and southeast.");

    set_no_exit_msg(({"south","southwest","west"}),
        "The Druedain Forest is too thick to enter from here.\n");

    add_exit(ANO_DIR + "road/wr8",  "southeast", 0, 3);
    add_exit(ANO_DIR + "road/wr10", "northwest", 0, 3);
    add_exit(ANO_DIR + "plains/an7w5n","east",0,5,1);
    add_exit(ANO_DIR + "plains/an7w4n","northeast",0,5,1);
    add_exit(ANO_DIR + "plains/an6w4n","north",0,5,1);
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