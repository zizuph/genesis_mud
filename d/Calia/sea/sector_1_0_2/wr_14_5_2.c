/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_1_0_2_room";

void
create_water_room()
{
    make_the_room("\n", 14, 5, 2);

    add_swim_exit(SECTOR_PATH(14,4,2)+"wr_14_4_2", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(14,6,2)+"wr_14_6_2", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(13,5,2)+"wr_13_5_2", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(15,5,2)+"wr_15_5_2", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(13,4,2)+"wr_13_4_2", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(13,6,2)+"wr_13_6_2", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(15,4,2)+"wr_15_4_2", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(15,6,2)+"wr_15_6_2", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(14,5,1)+"wr_14_5_1", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(14,5,3)+"wr_14_5_3", "down", 0, 2);
}
