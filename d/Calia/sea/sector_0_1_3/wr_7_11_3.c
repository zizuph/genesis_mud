/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_0_1_3_room";

void
create_water_room()
{
    make_the_room("\n", 7, 11, 3);

    add_swim_exit(SECTOR_PATH(7,10,3)+"wr_7_10_3", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(7,12,3)+"wr_7_12_3", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(6,11,3)+"wr_6_11_3", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(8,11,3)+"wr_8_11_3", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(6,10,3)+"wr_6_10_3", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(6,12,3)+"wr_6_12_3", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(8,10,3)+"wr_8_10_3", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(8,12,3)+"wr_8_12_3", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(7,11,2)+"wr_7_11_2", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(7,11,4)+"wr_7_11_4", "down", 0, 2);
}
