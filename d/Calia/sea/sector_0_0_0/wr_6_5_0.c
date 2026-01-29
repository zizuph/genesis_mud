/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_0_0_0_room";

#include "small_wkroug.h"

void
create_water_room()
{
    make_the_room("\n", 6, 5, 0);

    add_swim_exit(SECTOR_PATH(6,4,0)+"wr_6_4_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(6,6,0)+"wr_6_6_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(5,5,0)+"wr_5_5_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(7,5,0)+"wr_7_5_0", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(5,4,0)+"wr_5_4_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(5,6,0)+"wr_5_6_0", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(7,4,0)+"wr_7_4_0", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(7,6,0)+"wr_7_6_0", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(6,5,1)+"wr_6_5_1", "down", 0, 2);
    add_row_exit(SECTOR_PATH(6,4,0)+"wr_6_4_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(6,6,0)+"wr_6_6_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(5,5,0)+"wr_5_5_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(7,5,0)+"wr_7_5_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(5,4,0)+"wr_5_4_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(5,6,0)+"wr_5_6_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(7,4,0)+"wr_7_4_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(7,6,0)+"wr_7_6_0", "southwest", 0, 1);

    reset_room(); 
}

