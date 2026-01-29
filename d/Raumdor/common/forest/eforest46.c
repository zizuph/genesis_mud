/* East Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit EFOREST_ROOM;

void
create_room()
{
    string climb = "You scramble up the steep mountainside, " +
            "only to slide back down again.\n";
    forest_details = " To the east a steep mountainside rises " +
        "high above you.";
    ::create_room();
    add_item(({"mountain","mountains","mountainside"}),
            "Mountains rise from the forest, blocking passage east.\n");
    add_cmd_item(({"mountain","mountains","mountainside"}), "climb", climb);
    set_no_exit_msg(({"southeast","east","northeast"}), climb);
    add_exit(FOREST_DIR + "eforest49","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest37","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest36","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest45","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest48","northwest",0,FOREST_FATIGUE);
}
