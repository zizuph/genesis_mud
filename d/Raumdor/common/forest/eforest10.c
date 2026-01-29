/* East Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit EFOREST_ROOM;

void
create_room()
{
    string climb = "You scramble up the steep mountainside, " +
            "only to slide back down again.\n";
    forest_details = " To the south a steep mountainside rises " +
        "high above you.";
    ::create_room();
    add_item(({"mountain","mountains","mountainside"}),
            "Mountains rise from the forest, blocking passage south.\n");
    add_cmd_item(({"mountain","mountains","mountainside"}), "climb", climb);
    set_no_exit_msg(({"south","southeast"}), climb);
    add_exit(FOREST_DIR + "eforest18","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest19","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest11","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest03","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest09","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest17","northwest",0,FOREST_FATIGUE);
}
