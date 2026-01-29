/* West Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit WFOREST_ROOM;

void
create_room()
{
    string climb = "You scramble up the steep mountainside, " +
            "only to slide back down again.\n";
    forest_details = " To the southeast a steep mountainside rises high " +
        "above you.";
    ::create_room();
    add_item(({"mountain","mountains","mountainside"}),
            "Mountains rise from the forest, blocking passage " +
            "southeast.\n");
    add_cmd_item(({"mountain","mountains","mountainside"}), "climb", climb);
    set_no_exit_msg(({"southeast"}), climb);
    add_exit(FOREST_DIR + "wforest54","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest55","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest41","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest30","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest29","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest39","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest53","northwest",0,FOREST_FATIGUE);
}

