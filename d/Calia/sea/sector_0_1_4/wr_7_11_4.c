/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_0_1_4_room";

#include "eel.h"

void
create_water_room()
{
    make_the_room("\n", 7, 11, 4);

    add_swim_exit(SECTOR_PATH(7,10,4)+"wr_7_10_4", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(7,12,4)+"wr_7_12_4", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(6,11,4)+"wr_6_11_4", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(8,11,4)+"wr_8_11_4", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(6,10,4)+"wr_6_10_4", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(6,12,4)+"wr_6_12_4", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(8,10,4)+"wr_8_10_4", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(8,12,4)+"wr_8_12_4", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(7,11,3)+"wr_7_11_3", "up", 0, 0);
    reset_room();
}
