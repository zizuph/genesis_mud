/*
 *	/d/Gondor/anorien/road/wr8.c
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
    set_areadesc("field outside a dark forest");
    set_areatype(8);
    set_area("southwestern");
    set_areaname("Anorien");
    set_land("Gondor");
    set_mountain("Ered Nimrais, or the White Mountains");
    set_grass("light green, dry grass");
    set_extraline("To the east, the road enters a large forest, probably the "+
        "Druedain Forest, where the pukelmen live. A little further south "+
        "the Ered Nimrais, or the White Mountains, dominate the view, while " +
        "more plains stretch out both north and west. The road continues " +
        "northwest and east.");

    set_no_exit_msg(({"southeast","southwest","west","south"}),
        "The Druedain Forest is too thick to enter from here.\n");

    add_exit(ANO_DIR + "road/wr7", "east",      0, 3);
    add_exit(ANO_DIR + "road/wr9", "northwest", 0, 3);
    add_exit(ANO_DIR + "plains/an8w5n","northeast",0,5,1);
    add_exit(ANO_DIR + "plains/an7w5n","north",0,5,1);
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