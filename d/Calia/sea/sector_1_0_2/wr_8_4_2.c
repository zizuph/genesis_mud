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
    make_the_room("\n", 8, 4, 2);

    add_swim_exit(SECTOR_PATH(8,3,2)+"wr_8_3_2", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(8,5,2)+"wr_8_5_2", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(7,4,2)+"wr_7_4_2", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(9,4,2)+"wr_9_4_2", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(7,3,2)+"wr_7_3_2", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(7,5,2)+"wr_7_5_2", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(9,3,2)+"wr_9_3_2", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(9,5,2)+"wr_9_5_2", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(8,4,1)+"wr_8_4_1", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(8,4,3)+"wr_8_4_3", "down", 0, 2);
}
