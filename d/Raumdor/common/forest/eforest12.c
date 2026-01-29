/* East Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit EFOREST_ROOM;

void
create_room()
{
    string climb = "You scramble up the steep mountainside, " +
            "only to slide back down again.\n";
    forest_details = " To the southwest a steep mountainside rises " +
        "high above you.";
    ::create_room();
    add_item(({"mountain","mountains","mountainside"}),
            "Mountains rise from the forest, blocking passage southwest.\n");
    add_cmd_item(({"mountain","mountains","mountainside"}), "climb", climb);
    set_no_exit_msg(({"southwest"}), climb);
    add_exit(FOREST_DIR + "eforest20","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest21","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest13","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest05","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest04","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest44","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest58","northwest",0,FOREST_FATIGUE);
}
