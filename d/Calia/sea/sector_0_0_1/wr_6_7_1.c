/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_0_0_1_room";

void
create_water_room()
{
    make_the_room("\n", 6, 7, 1);

    add_swim_exit(SECTOR_PATH(6,6,1)+"wr_6_6_1", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(6,8,1)+"wr_6_8_1", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(5,7,1)+"wr_5_7_1", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(7,7,1)+"wr_7_7_1", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(5,6,1)+"wr_5_6_1", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(5,8,1)+"wr_5_8_1", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(7,6,1)+"wr_7_6_1", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(7,8,1)+"wr_7_8_1", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(6,7,0)+"wr_6_7_0", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(6,7,2)+"wr_6_7_2", "down", 0, 2);
}
