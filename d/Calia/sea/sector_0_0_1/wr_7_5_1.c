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
    make_the_room("\n", 7, 5, 1);

    add_swim_exit(SECTOR_PATH(7,4,1)+"wr_7_4_1", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(7,6,1)+"wr_7_6_1", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(6,5,1)+"wr_6_5_1", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(8,5,1)+"wr_8_5_1", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(6,4,1)+"wr_6_4_1", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(6,6,1)+"wr_6_6_1", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(8,4,1)+"wr_8_4_1", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(8,6,1)+"wr_8_6_1", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(7,5,0)+"wr_7_5_0", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(7,5,2)+"wr_7_5_2", "down", 0, 2);
}
