/*
 * Road in Bree
 * By Finwe, June  2001
 * Jan 2019: Finwe, Added treetop fort description
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h" 
#include "defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/sys/cmdparse.h"
#include "/secure/std.h"
#include "/sys/tasks.h"


inherit ROAD_BASE;

void
create_road_room()
{

    set_areadesc("ancient highway");
    set_area("north of");
    set_areaname("Bree");
    set_land("Eriador");

    set_extraline("Old and deserted, the ancient highway appears to have " +
        "once been well travelled. Gray stone blocks look like they once " +
        "paved the highway, but are now cracked and buckled with age. An " +
        "air of despair fills the area. Following the eastern edge of the " +
        "highway, you can see the tall hedge that surrounds the village " +
        "of Bree.\n");

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

    add_exit(ROAD_DIR + "nroad03", "north", "@@tree_north@@");
    add_exit(ROAD_DIR + "nroad01", "south", "@@tree_south@@");
}

void tree_north()
{
    tell_tree_fort("went north towards Fornost and disappears.");
}

void tree_south()
{
    tell_tree_fort("went south along the old highway.\n");
}