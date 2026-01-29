/* West Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit WFOREST_ROOM;

void
create_room()
{
    forest_intro = "You are near the fringes of a dark forest.";
    forest_features = " Trees and darkness continue in all directions, " +
        "except south and southwest, where trees disperse. Directly south, " +
       "the land turns into a lifeless plain. Further west is an " +
       "empty coastline.";
    ::create_room();
    add_item(({"waters","coast","gulf"}), 
            "The sea gently rolls in the wind.\n");
    add_item(({"plain","flats"}),
            "The flats extend south into the mountains. They look barren.\n");
    add_item(({"mountains"}), "Mountains rise from the flats far to the " +
            "south.\n");
    set_no_exit_msg("southwest",
            "Cold waters dissuade you from proceeding that way.\n");
    add_exit(FOREST_DIR + "wforest11","northwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest12","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest13","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest03","east",0,FOREST_FATIGUE);
    add_exit(SFLATS_DIR + "sflats02","southeast",0,FOREST_FATIGUE);
    add_exit(SFLATS_DIR + "sflats01","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest01","west",0,FOREST_FATIGUE);
}

