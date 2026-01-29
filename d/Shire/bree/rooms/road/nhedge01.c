/*
 * Road in Bree
 * By Finwe, June  2001
 */
 
#include "/d/Shire/sys/defs.h"
#include "defs.h"

inherit ROAD_BASE;
 
void
create_road_room()
{
//    set_areadesc("small");
//    set_area("path");
//    set_areaname("outside the hedge");
//    set_land("Bree");

    add_bree_desc("The path winds its way between a large dike to " +
        "the west and a very tall hedge to the east. Both are the " +
        "major defenses of the town of bree, and protect it from " +
        "invaders.\n");

    set_add_hedge_road();
    set_add_bushes();

    add_exit(ROAD_DIR + "nhedge02", "north", "@@tree_north@@");
    add_exit(ROAD_DIR + "wgate",    "south", "@@tree_south@@");

}

void tree_north()
{
    tell_room("/d/Shire/bree/rooms/road/treetop_fort.c", QCTNAME(TP) +" heads north along the hedge outside Bree.\n");
}

void tree_south()
{
    tell_room("/d/Shire/bree/rooms/road/treetop_fort.c", QCTNAME(TP) +" heads south to Bree.\n");
}