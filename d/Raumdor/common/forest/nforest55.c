/* North Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit NFOREST_ROOM;

void
create_room()
{
    string climb = "You scramble up the steep mountainside, " +
            "only to slide back down again.\n";
    forest_details = " To the northwest a steep mountainside rises high " +
        "above you.";
    ::create_room();
    add_item(({"mountain","mountains","mountainside"}),
            "Mountains rise from the forest, blocking passage " +
            "northwest.\n");
    add_cmd_item(({"mountain","mountains","mountainside"}), "climb", climb);
    set_no_exit_msg(({"west","northwest","north","northeast"}), climb);
    add_exit(FOREST_DIR + "nforest56","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest49","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest48","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest47","southwest",0,FOREST_FATIGUE);
}

