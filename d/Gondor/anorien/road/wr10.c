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
    set_areadesc("green, grassy field");
    set_areatype(8);
    set_area("western");
    set_areaname("Anorien");
    set_land("Gondor");
    set_mountain("White Mountains");
    set_grass("dark green grass");
    set_extraline("The road continues west across the plains of Anorien, " +
        "and southeast towards a large forest. To the south the White " +
        "Mountains dominate the view. A valley opens between the hills at " +
        "the foot of the mountains to the south.");

    set_no_exit_msg(({"southwest"}),
        "The broken foothills of the White Mountains are too difficult " +
        "for you to climb from here. Perhaps you should follow the " +
        "path south into the valley instead.\n");

    add_exit(ANO_DIR + "road/wr11",          "west",      0, 3);
    add_exit(ANO_DIR + "road/wr9",           "southeast", 0, 3);
    add_exit(ANO_DIR + "nimrais/rimvalley1", "south",     0, 2);
    add_exit(ANO_DIR + "plains/an4w3n","northwest",0,5,1);
    add_exit(ANO_DIR + "plains/an6w3n","northeast",0,5,1);
    add_exit(ANO_DIR + "plains/an5w3n","north",0,5,1);
    add_exit(ANO_DIR + "plains/an6w4n","east",0,5,1);
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