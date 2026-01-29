/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_0_0_2_room";

void
create_water_room()
{
    make_the_room("\n", 7, 7, 2);

    add_swim_exit(SECTOR_PATH(7,6,2)+"wr_7_6_2", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(7,8,2)+"wr_7_8_2", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(6,7,2)+"wr_6_7_2", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(8,7,2)+"wr_8_7_2", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(6,6,2)+"wr_6_6_2", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(6,8,2)+"wr_6_8_2", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(8,6,2)+"wr_8_6_2", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(8,8,2)+"wr_8_8_2", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(7,7,1)+"wr_7_7_1", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(7,7,3)+"wr_7_7_3", "down", 0, 2);
}
