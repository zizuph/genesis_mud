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

    set_extraline("Few travellers seem to venture this way, except " +
        "for the very brave. The desolate hills here have very little " +
        "growth and appear almost barren and haunted. The ancient highway " +
        "you are following is cracked and the stones have buckled, leaving " +
        "a variety of grasses and weeds to flourish instead.\n");

    add_item(({"bree", "village"}),
        "Off in the distance to the south is the small village of Bree. You " +
        "cannot really see much from here however.\n");
    add_item(({"hill", "hills"}),
        "The land here is filled with empty hills, with nothing much to see " +
        "save an old broken highway.\n");

    set_no_exit_msg(({"east","northeast"}),
        "You wander slightly off the road into the barren and desolate " +
        "hills that fill the land. But you find the land very difficult " +
        "to pass through, and swiftly move back to the highway instead. " +
        "You happen to notice a small path cutting east across the hills " +
        "just north of here however. If you follow this highway north, you " +
        "should get there quickly.\n");
    set_no_exit_msg(({"west","southwest","northwest","southeast"}),
        "You wander slightly off the road into the barren and desolate " +
        "hills that fill the land. But you find the land very difficult " +
        "to pass through, and swiftly move back to the highway instead.\n");

    set_add_nroad();

    add_exit(ROAD_DIR + "nroad06", "north");
    add_exit(ROAD_DIR + "nroad04", "south");
}
