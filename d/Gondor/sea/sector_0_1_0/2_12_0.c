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
    make_the_room("\n", 2, 12, 0);

    add_swim_exit(SECTOR_PATH(2,11,0)+"2_11_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(2,13,0)+"2_13_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(1,12,0)+"1_12_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(3,12,0)+"3_12_0", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(1,11,0)+"1_11_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(1,13,0)+"1_13_0", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(3,11,0)+"3_11_0", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(3,13,0)+"3_13_0", "southwest", 0, 1);
    add_row_exit(SECTOR_PATH(2,11,0)+"2_11_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(2,13,0)+"2_13_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(1,12,0)+"1_12_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(3,12,0)+"3_12_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(1,11,0)+"1_11_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(1,13,0)+"1_13_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(3,11,0)+"3_11_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(3,13,0)+"3_13_0", "southwest", 0, 1);
}
