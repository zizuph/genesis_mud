/* West Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit WFOREST_ROOM;

void
create_room()
{
    forest_intro = "You are near the fringes of a dark forest.";
    forest_features = " Trees and darkness continue in all directions but " +
        "south, where the trees disperse into a barren plain."; 
    ::create_room();
    add_item(({"plain","flats"}),
            "The flats extend south into the mountains. They look lifeless.\n");
    add_item(({"mountains"}), "Mountains rise from the flats far to the " +
            "south.\n");
    add_exit(FOREST_DIR + "wforest13","northwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest14","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest15","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest05","east",0,FOREST_FATIGUE);
    add_exit(SFLATS_DIR + "sflats04","southeast",0,FOREST_FATIGUE);
    add_exit(SFLATS_DIR + "sflats03","south",0,FOREST_FATIGUE);
    add_exit(SFLATS_DIR + "sflats02","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest03","west",0,FOREST_FATIGUE);
}
