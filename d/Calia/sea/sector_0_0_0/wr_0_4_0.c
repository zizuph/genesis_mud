/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

  Beach connected, Maniac, 30/7/96
*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_0_0_0_room";

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
    make_the_room("\n", 0, 4, 0);

    add_wade_exit(WATER+"beach/beach1", "east", 0, 1); 
    add_wade_exit(SECTOR_PATH(0,5,0)+"wr_0_5_0", "south", 0, 1);
    add_wade_exit(SECTOR_PATH(1,4,0)+"wr_1_4_0", "west", 0, 1);
    add_wade_exit(SECTOR_PATH(1,5,0)+"wr_1_5_0", "southwest", 0, 1);
    add_row_exit(SECTOR_PATH(0,5,0)+"wr_0_5_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(1,4,0)+"wr_1_4_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(1,5,0)+"wr_1_5_0", "southwest", 0, 1);

    reset_room(); 
}

