/* East Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit EFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "eforest29","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest30","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest21","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest13","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest12","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest44","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest58","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest72","northwest",0,FOREST_FATIGUE);
}
