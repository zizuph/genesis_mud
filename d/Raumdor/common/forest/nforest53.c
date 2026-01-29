/* North Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit NFOREST_ROOM;

void
create_room()
{
    string climb = "You scramble up the steep mountainside, " +
            "only to slide back down again.\n";
    forest_details = " To the north a steep mountainside rises high " +
        "above you.";
    ::create_room();
    add_item(({"mountain","mountains","mountainside"}),
            "Mountains rise from the forest, blocking passage " +
            "north.\n");
    add_cmd_item(({"mountain","mountains","mountainside"}), "climb", climb);
    set_no_exit_msg(({"northwest","north","northeast"}), climb);
    add_exit(FOREST_DIR + "nforest54","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest45","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest44","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest43","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest52","west",0,FOREST_FATIGUE);
}

