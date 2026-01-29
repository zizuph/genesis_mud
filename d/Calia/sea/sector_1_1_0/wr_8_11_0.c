/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/
inherit "/d/Calia/sea/std/sector_1_1_0_room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"
#include "turtle.h"


void
create_water_room()
{
    make_the_room("\n", 8, 11, 0);

    add_swim_exit(SECTOR_PATH(8,10,0)+"wr_8_10_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(8,12,0)+"wr_8_12_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(7,11,0)+"wr_7_11_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(9,11,0)+"wr_9_11_0", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(7,10,0)+"wr_7_10_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(7,12,0)+"wr_7_12_0", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(9,10,0)+"wr_9_10_0", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(9,12,0)+"wr_9_12_0", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(8,11,1)+"wr_8_11_1", "down", 0, 2);
    add_row_exit(SECTOR_PATH(8,10,0)+"wr_8_10_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(8,12,0)+"wr_8_12_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(7,11,0)+"wr_7_11_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(9,11,0)+"wr_9_11_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(7,10,0)+"wr_7_10_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(7,12,0)+"wr_7_12_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(9,10,0)+"wr_9_10_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(9,12,0)+"wr_9_12_0", "southwest", 0, 1);

    reset_room(); 
}
