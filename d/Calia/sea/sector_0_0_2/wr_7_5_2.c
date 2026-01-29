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
    make_the_room("\n", 7, 5, 2);

    add_swim_exit(SECTOR_PATH(7,4,2)+"wr_7_4_2", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(7,6,2)+"wr_7_6_2", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(6,5,2)+"wr_6_5_2", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(8,5,2)+"wr_8_5_2", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(6,4,2)+"wr_6_4_2", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(6,6,2)+"wr_6_6_2", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(8,4,2)+"wr_8_4_2", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(8,6,2)+"wr_8_6_2", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(7,5,1)+"wr_7_5_1", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(7,5,3)+"wr_7_5_3", "down", 0, 2);
}
