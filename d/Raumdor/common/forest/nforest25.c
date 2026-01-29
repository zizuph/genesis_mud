/* North Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit NFOREST_ROOM;

void
create_room()
{
    forest_intro = "You are near the fringes of a dark forest.";
    forest_features = " Trees and darkness continue in all directions but " +
        "northwest, where the trees disperse into a barren plain."; 
    ::create_room();
    add_item(({"plain","flats"}),
            "The flats extend north into the mountains. They look lifeless.\n");
    add_item(({"mountains"}), "Mountains rise from the flats far to the " +
            "north.\n");
    add_exit(NFLATS_DIR + "nflats22","northwest",0,FOREST_FATIGUE);
    add_exit(NFLATS_DIR + "nflats23","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest37","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest26","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest14","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest13","south",0,FOREST_FATIGUE);
    add_exit(NFLATS_DIR + "nflats19","west",0,FOREST_FATIGUE);
    add_exit(NFLATS_DIR + "nflats15","southwest",0,FOREST_FATIGUE);
}
