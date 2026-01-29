/*
 *	/d/Gondor/anorien/road/wr12.c
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

static object  Monster;

public void
create_area_room()
{
    set_areadesc("green, grassy field");
    set_areatype(8);
    set_area("northwest");
    set_areaname("Anorien");
    set_land("Gondor");
    set_mountain("");
    set_grass("medium, juicy green grass");
    set_forest("Taur-nan-Anvar");
    set_extraline("All the way from west to east, through north, Anorien " +
        "is coated by juicy green grass. South, Taur-nan-Anvar covers the " +
	    "horizon. The road comes out of the forest from the northwest, " +
        "and continues out on the plains of Anorien to the east.");

    set_no_exit_msg(({"southwest","south","west","southeast"}),
        "The dense foliage of the Firien Wood is too thick here for " +
        "you to enter. You will probably have to follow the road from " +
        "here.\n");

    add_exit(ANO_DIR + "road/wr11", "east",      0, 3);
    add_exit(ANO_DIR + "road/wr13", "northwest", 0, 3);
    add_exit(ANO_DIR + "plains/an3w3n","north",0,5,1);
    add_exit(ANO_DIR + "plains/an4w3n","northeast",0,5,1);

    reset_room();
}

public void
reset_room()
{
    Monster = clone_npc(Monster, NPC_DIR + "owl");

    if (!objectp(present("jacket", TO)))
	clone_object(ARM_DIR + "fjacket")->move(TO);
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