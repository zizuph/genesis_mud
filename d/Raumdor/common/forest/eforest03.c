/* East Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit EFOREST_ROOM;

void
create_room()
{
    string climb = "You scramble up the steep mountainside, " +
            "only to slide back down again.\n";
    forest_details = " To the southeast a steep mountainside rises " +
        "high above you.";
    ::create_room();
    add_item(({"mountain","mountains","mountainside"}),
            "Mountains rise from the forest, blocking passage southeast.\n");
    add_cmd_item(({"mountain","mountains","mountainside"}), "climb", climb);
    set_no_exit_msg(({"southwest","south","southeast","east"}), climb);
    add_exit(FOREST_DIR + "eforest09","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest10","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest02","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest08","northwest",0,FOREST_FATIGUE);
}
