/*
  Southwest area of Bay of Belfalas near Tolfalas island.

  Palmer - Aug 2006

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Gondor/sea/sector_1_1_0/sector_room";

void
create_water_room()
{
    make_the_room("\n", 10, 12, 0);

    add_swim_exit(SECTOR_PATH(10,11,0)+"10_11_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(10,13,0)+"10_13_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(9,12,0)+"9_12_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(11,12,0)+"11_12_0", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(9,11,0)+"9_11_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(9,13,0)+"9_13_0", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(11,11,0)+"11_11_0", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(11,13,0)+"11_13_0", "southwest", 0, 1);
    add_row_exit(SECTOR_PATH(10,11,0)+"10_11_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(10,13,0)+"10_13_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(9,12,0)+"9_12_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(11,12,0)+"11_12_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(9,11,0)+"9_11_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(9,13,0)+"9_13_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(11,11,0)+"11_11_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(11,13,0)+"11_13_0", "southwest", 0, 1);
}
