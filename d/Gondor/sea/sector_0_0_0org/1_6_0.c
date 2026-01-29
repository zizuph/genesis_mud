/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Gondor/sea/sector_0_0_0/sector_room";

void
create_water_room()
{
    make_the_room("\n", 1, 6, 0);

    add_wade_exit(SECTOR_PATH(1,5,0)+"1_5_0", "north", 0, 1);
    add_wade_exit(SECTOR_PATH(1,7,0)+"1_7_0", "south", 0, 1);
    add_wade_exit(SECTOR_PATH(0,6,0)+"0_6_0", "east", 0, 1);
    add_wade_exit(SECTOR_PATH(2,6,0)+"2_6_0", "west", 0, 1);
    add_wade_exit(SECTOR_PATH(0,5,0)+"0_5_0", "northeast", 0, 1);
    add_wade_exit(SECTOR_PATH(0,7,0)+"0_7_0", "southeast", 0, 1);
    add_wade_exit(SECTOR_PATH(2,5,0)+"2_5_0", "northwest", 0, 1);
    add_wade_exit(SECTOR_PATH(2,7,0)+"2_7_0", "southwest", 0, 1);
    add_row_exit(SECTOR_PATH(1,5,0)+"1_5_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(1,7,0)+"1_7_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(0,6,0)+"0_6_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(2,6,0)+"2_6_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(0,5,0)+"0_5_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(0,7,0)+"0_7_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(2,5,0)+"2_5_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(2,7,0)+"2_7_0", "southwest", 0, 1);
}
