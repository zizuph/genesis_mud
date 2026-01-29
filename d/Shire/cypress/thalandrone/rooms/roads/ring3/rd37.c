/*
 * Road in Third Ring of Thalandor
 * By Finwe, July 2001
 */
 
#pragma strict_types
#include "/d/Shire/cypress/sys/defs.h" 
#include "local.h"

inherit ROAD_BASE;
 
void create_road_room()
{
    set_areaname("third ring");
    set_areadesc("street");
    set_vbfc_extra(road_desc4);

    add_my_desc("A path leads northwest out of Thalandrone and a " +
        "stately building is south.\n");
    add_item("path",
        "The path is wide and set with white stone blocks. It " +
        "leads northwest out of the city.\n");
    add_item("stately building",
        "The stately build is one story and fashioned of white " +
        "stone. It is  surrounded by gardens and ancient trees. " +
        "A column of white stone is set to the left side of the " + 
        "entrance.\n");
    add_item("entrance",
        "The entrance is wide with an arched top leading into " +
        "the building.");
    add_item(({"top", "arched top"}),
        "The top is fashioned from one piece of white stone and " +
        "set on to the top of the entrance.\n");
    add_item(({"marker", "column", "column of white stone"}),
        "The column is about waist high and circular. In golden " +
        "letters and engraved on the front it reads, " +
        "'Guild of the Wild Elves'\n");

    add_exit(RD3_DIR + "rd38",     "east");
    add_exit(WRUNNER_DIR + "join", "south");
    add_exit(OTHERS_DIR + "av01",  "southeast");
    add_exit(RD3_DIR + "rd36",     "southwest");
 
}

