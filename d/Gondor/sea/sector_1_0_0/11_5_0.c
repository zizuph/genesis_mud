/*
  A room in the Bay of Belfalas near Tolfalas island.

  Palmer - Aug 24, 2006

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Gondor/sea/sector_1_0_0/sector_room";

void
create_water_room()
{
    make_the_room("\n", 11, 5, 0);

    add_swim_exit(SECTOR_PATH(11,4,0)+"11_4_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(11,6,0)+"11_6_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(10,5,0)+"10_5_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(12,5,0)+"12_5_0", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(10,4,0)+"10_4_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(10,6,0)+"10_6_0", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(12,4,0)+"12_4_0", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(12,6,0)+"12_6_0", "southwest", 0, 1);
    add_row_exit(SECTOR_PATH(11,4,0)+"11_4_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(11,6,0)+"11_6_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(10,5,0)+"10_5_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(12,5,0)+"12_5_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(10,4,0)+"10_4_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(10,6,0)+"10_6_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(12,4,0)+"12_4_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(12,6,0)+"12_6_0", "southwest", 0, 1);
}
