/* East Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit EFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "eforest21","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest22","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest14","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest06","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest05","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest04","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest12","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest20","northwest",0,FOREST_FATIGUE);
}
