/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_0_1_0_room";

object crab;

void
reset_room()
{
    if (!objectp(crab)) {
        crab = clone_object(SEA_CREATURES+"crab");
        crab->move_living("into the sea", this_object());
    }
}


void
create_water_room()
{
    make_the_room("\n", 1, 13, 0);

    add_wade_exit(SECTOR_PATH(1,12,0)+"wr_1_12_0", "north", 0, 1);
    add_wade_exit(SECTOR_PATH(2,13,0)+"wr_2_13_0", "west", 0, 1);
    add_wade_exit(SECTOR_PATH(0,12,0)+"wr_0_12_0", "northeast", 0, 1);
    add_wade_exit(SECTOR_PATH(2,12,0)+"wr_2_12_0", "northwest", 0, 1);
    add_wade_exit(SECTOR_PATH(2,14,0)+"wr_2_14_0", "southwest", 0, 1);
    add_row_exit(SECTOR_PATH(1,12,0)+"wr_1_12_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(2,13,0)+"wr_2_13_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(0,12,0)+"wr_0_12_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(2,12,0)+"wr_2_12_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(2,14,0)+"wr_2_14_0", "southwest", 0, 1);

    reset_room(); 
}

