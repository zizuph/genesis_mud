/* West Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit WFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "wforest86","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest38","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest29","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest20","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest58","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest57","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest71","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest85","northwest",0,FOREST_FATIGUE);
}

