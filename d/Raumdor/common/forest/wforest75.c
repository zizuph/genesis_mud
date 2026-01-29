/* West Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit WFOREST_ROOM;
 
void
create_room()
{
    forest_intro = "You are near the fringes of a dark forest.";
    forest_features = " Trees and darkness continue in all directions but " +
        "north, where the trees disperse into a barren plain."; 
    ::create_room();
    add_item(({"plain","flats"}),
            "The flats extend north into the mountains. They look lifeless.\n");
    add_item(({"mountains"}), "Mountains rise from the flats far to the " +
            "north.\n");
    add_exit(NFLATS_DIR + "nflats02","northwest",0,FOREST_FATIGUE);
    add_exit(NFLATS_DIR + "nflats03","north",0,FOREST_FATIGUE);
    add_exit(NFLATS_DIR + "nflats04","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest62","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest76","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest61","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest74","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest60","southwest",0,FOREST_FATIGUE);
}

