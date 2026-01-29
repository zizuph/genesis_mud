/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"
#define PYROS_CAVE "/d/Calia/sea/pyros/entrance"

inherit "/d/Calia/sea/std/sector_1_1_4_room";

void
create_water_room()
{
    make_the_room("\n", 15, 8, 4);

    add_item(({"sooty residue","residue"}),"Through the residue you notice "+
        "a small opening in the rock wall of the volcano.\n");

    add_item(({"small opening","opening"}),"It appears this was once the" +
        " entrance to a cave, but it has now been blocked by large" +
        " boulders.\n");     

    add_swim_exit(SECTOR_PATH(15,7,4)+"wr_15_7_4", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(15,9,4)+"wr_15_9_4", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(14,8,4)+"wr_14_8_4", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(14,7,4)+"wr_14_7_4", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(14,9,4)+"wr_14_9_4", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(15,8,3)+"wr_15_8_3", "up", 0, 0);
}

int
do_crawl(string str)
{
    if (!str || str != "through opening")
    {
        NF("Crawl through what?\n");
        return 0;
    }

    NF("You couldn't possibly crawl through there anymore, it's been" +
        " completely blocked by many large boulders!\n");
    return 0;
}

void
init()
{
    ::init();
    add_action("do_crawl","crawl");
}
