/*
 * Road in Bree
 * By Finwe, June  2001
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h" 
#include "defs.h"

inherit ROAD_BASE;

void
create_road_room()
{
    set_areadesc("ancient highway");
    set_area("north of");
    set_areaname("Bree");
    set_land("Eriador");

    set_extraline("You are on an ancient highway, which cuts across empty " +
        "hills in a land that is quiet, almost deathly still. The broken " +
        "stone blocks of the road still run in a straight line to the " +
        "north and south, while the tall hedge which surrounds the village " +
        "of Bree follows the eastern edge of the roadside.\n");

    add_item(({"hedge", "tall hedge"}),
        "This tall hedge follows the eastern edge of the highway, and " +
        "surrounds the village of Bree, offering protection " +
        "from bandits or invaders.\n");
    add_item(({"bree", "village"}),
        "The village of Bree stands just east of the highway here, on " +
        "the other side of the tall hedge beside you.\n");
    add_item(({"hill", "hills"}),
        "The land here is filled with empty hills, with nothing much to see " +
        "save an old broken highway and the small village of Bree.\n");

    set_no_exit_msg(({"east","southeast","northeast"}),
        "The hedge is too thick here, you will need to find another way " +
        "into Bree.\n");
    set_no_exit_msg(({"west","southwest","northwest"}),
        "You wander slightly off the road into the barren and desolate " +
        "hills that fill the land. But you find the land very difficult " +
        "to pass through, and swiftly move back to the highway instead.\n");

    set_add_nroad();

    add_exit(ROAD_DIR + "nroad04", "north");
    add_exit(ROAD_DIR + "nroad02", "south");
}
