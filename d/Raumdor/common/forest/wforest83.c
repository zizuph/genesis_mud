/* The road through the forest of Raumdor, by Sarr */
/* 2017-06-26 Malus: Spawn fix and standardization */ 
#include "defs.h"
inherit FOREST_ROAD_ROOM;

void
create_room()
{
    ::create_room();
    set_long("@@road_long@@You see some kind of structure to the south " +
            "and a bridge to the east.\n");
    add_item("structure","It looks like the remains of a ruined tower.\n");
    add_item("bridge","You are too far away to see it very well.\n");
    add_exit(FOREST_DIR + "nforest03","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest04","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest84","east");
    add_exit(FOREST_DIR + "wforest70","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest69","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest68","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest82","west");
    add_exit(FOREST_DIR + "nforest02","northwest",0,FOREST_FATIGUE);
}
