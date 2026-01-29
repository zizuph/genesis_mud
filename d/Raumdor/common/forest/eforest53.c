/* The road through the forest of Raumdor, by Sarr */
#include "defs.h"
inherit FOREST_ROAD_ROOM;

void
create_room()
{
    roadEast = "northeast";
    roadWest = "southwest";
    ::create_room();
    set_short("On an old path, nearing a mountain trail");
    set_long("You are on an old pathway, a scattering of cobblestones that " +
            "stop abruptly at the start a mountain trail to the northeast. " +
            "The forest surrounds the path on the western and southern " +
            "sides. The path itself continues southwest." +
            "@@day_description@@\n");
    add_item(({"trail"}),"A dirt path that leads up into the pass.\n");
    add_exit(MTRAIL_DIR + "mtrail01","northeast");
    add_exit(FOREST_DIR + "eforest51","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest50","southwest");
    add_exit(FOREST_DIR + "eforest52","west",0,FOREST_FATIGUE);
}

string
day_description()
{
    if (DAY)
        return " The trees enclose the path tightly, but light from above " +
            "still shines through. You feel the path would provide some " +
            "protection from the darkness that flanks it, at least now " +
            "during the day.";
    return "";
}
