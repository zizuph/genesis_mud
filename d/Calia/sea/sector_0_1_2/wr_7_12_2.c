/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_0_1_2_room";

void
create_water_room()
{
    make_the_room("\n", 7, 12, 2);

    add_swim_exit(SECTOR_PATH(7,11,2)+"wr_7_11_2", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(7,13,2)+"wr_7_13_2", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(6,12,2)+"wr_6_12_2", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(8,12,2)+"wr_8_12_2", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(6,11,2)+"wr_6_11_2", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(6,13,2)+"wr_6_13_2", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(8,11,2)+"wr_8_11_2", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(8,13,2)+"wr_8_13_2", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(7,12,1)+"wr_7_12_1", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(7,12,3)+"wr_7_12_3", "down", 0, 2);
}
