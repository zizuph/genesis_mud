/*
* Entrance yard to Smiths Guild
* By Finwe, June 2002
*/

#pragma strict_types

#include "/d/Shire/sys/defs.h" 
#include "/d/Shire/bree/defs.h"

inherit ROAD_BASE;

#include "smiths.h"

// object gate;

void
create_road_room()
{
set_areadesc("large");
set_area("open");
set_areaname("plaza");
set_land("the Blacksmiths guild");

    add_my_desc("Some tall buildings surround the the plaza with " +
        "other smaller buildings to the north. This is the Blacksmiths, " +
        "where those interested in the art of forging come to learn " +
        "their trade. The plaza is large, and often filled with " +
        "people who come from all over to learn the trade, to " +
        "purchase items, or have things repaired.\n");

//    gate = clone_object(OBJ_DIR + "smith_gate");
//    gate -> move(this_object());

    add_item(({"plaza"}),
        "The plaza is large and square shaped and set with smooth " +
        "blocks of stone. Paths lead from the plaza to the buildings " +
        "that surround the Plaza.\n");
    add_item(({"paths", "path"}),
        "Paths lead from the plaza to the buildings that surround " +
        "it. The paths are made of smooth blocks of stone.\n");
    add_item(({"buildings"}),
        "The buildings are all different sizes. Some are tall and " +
        "several stories while others are short and one story. They " +
        "line the plaza and are where the Blacksmiths learn their " +
        "trade or where traders come for assistance. The builds are " +
        "made of stone and are expertly constructed.\n");
    add_item(({"stone", "smooth stone blocks", "stone blocks"}),
        "The stone blocks are smooth and large. They are gray colored " +
        "and are expertly carved. Some are set in the ground, making " +
        "up the plaza and paths while others are used in the " +
        "construction of the buildings. Still others are used to " +
        "make up the wall that surrounds the guild.\n");
    add_item(({"wall"}),
        "The wall is constructed of many stone blocks. It surrounds " +
        "the guild, protecting those who are inside.\n");
    add_item(({"gate", "steel gate", "ornate gate", "ornate steel gate"}),
        "The ornate steel gate is beautifully wrought of polished " +
        "steel. It is forged of polished vertical, steel bars with a " +
        "horizontal bar at the top and bottom of the gate. On top " +
        "of each vertical bar is a round ball.\n");
    add_item(({"round ball"}),
        "The round balls are set on top of each vertical bar of the " +
        "gate. They are fist size and polished.\n");

    add_exit("/d/Shire/bree/rooms/road/broad07", "east");
    add_exit(SMITHSDIR_ROOMS + "entrance", "west");
}
