/* West Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit WFOREST_ROOM;

void
create_room()
{
    string climb = "You scramble up the steep mountainside, " +
            "only to slide back down again.\n";
    forest_intro = "You are near the fringes of a dark forest.";
    forest_features = " Trees and darkness continue in all directions but " +
        "south, where trees disperse into a barren plain.";
    forest_details = " To the southeast a steep mountainside rises high " +
        "above you.";
    ::create_room();
    add_item(({"plain","flats"}),
            "The flats extend south into the mountains. They look lifeless.\n");
    add_item(({"mountain","mountains","mountainside"}),
            "Mountains rise from the forest, blocking passage south.\n");
    add_cmd_item(({"mountain","mountains","mountainside"}), "climb", climb);
    set_no_exit_msg("southeast", climb);
    add_exit(FOREST_DIR + "wforest17","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest18","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest08","east",0,FOREST_FATIGUE);
    add_exit(SFLATS_DIR + "sflats06","south",0,FOREST_FATIGUE);
    add_exit(SFLATS_DIR + "sflats05","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest06","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest16","northwest",0,FOREST_FATIGUE);
}

