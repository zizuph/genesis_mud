/*
  Southeast Bay of Belfalas near Tolfalas Island.

 Palmer - Aug 2006

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Gondor/sea/sector_0_1_0/sector_room";

void
create_water_room()
{
    make_the_room("\n", 4, 11, 0);

    add_swim_exit(SECTOR_PATH(4,10,0)+"4_10_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(4,12,0)+"4_12_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(3,11,0)+"3_11_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(5,11,0)+"5_11_0", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(3,10,0)+"3_10_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(3,12,0)+"3_12_0", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(5,10,0)+"5_10_0", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(5,12,0)+"5_12_0", "southwest", 0, 1);
    add_row_exit(SECTOR_PATH(4,10,0)+"4_10_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(4,12,0)+"4_12_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(3,11,0)+"3_11_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(5,11,0)+"5_11_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(3,10,0)+"3_10_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(3,12,0)+"3_12_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(5,10,0)+"5_10_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(5,12,0)+"5_12_0", "southwest", 0, 1);
}
