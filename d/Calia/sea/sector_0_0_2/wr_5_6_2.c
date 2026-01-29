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
    make_the_room("\n", 5, 6, 2);

    add_swim_exit(SECTOR_PATH(5,5,2)+"wr_5_5_2", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(5,7,2)+"wr_5_7_2", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(4,6,2)+"wr_4_6_2", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(6,6,2)+"wr_6_6_2", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(4,5,2)+"wr_4_5_2", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(4,7,2)+"wr_4_7_2", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(6,5,2)+"wr_6_5_2", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(6,7,2)+"wr_6_7_2", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(5,6,1)+"wr_5_6_1", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(5,6,3)+"wr_5_6_3", "down", 0, 2);
}
