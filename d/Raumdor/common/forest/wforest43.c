/* West Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit WFOREST_ROOM;

void
create_room()
{
    string climb = "You scramble up the steep mountainside, " +
            "only to slide back down again.\n";
    forest_details = " To the south a steep mountainside rises high above you.";
    ::create_room();
    add_item(({"mountain","mountains","mountainside"}),
            "Mountains rise from the forest, blocking passage south.\n");
    add_cmd_item(({"mountain","mountains","mountainside"}), "climb", climb);
    set_no_exit_msg(({"southwest","south","southeast"}), climb);
    add_exit(FOREST_DIR + "wforest57","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest58","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest56","northwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest42","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest44","east",0,FOREST_FATIGUE);
}
