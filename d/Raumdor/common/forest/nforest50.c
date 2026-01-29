/* North Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit NFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "nforest57","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest58","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest51","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest42","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest41","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest40","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest49","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest56","northwest",0,FOREST_FATIGUE);
}

