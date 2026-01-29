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
    make_the_room("\n", 7, 12, 0);

    add_swim_exit(SECTOR_PATH(7,11,0)+"7_11_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(7,13,0)+"7_13_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(6,12,0)+"6_12_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(8,12,0)+"8_12_0", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(6,11,0)+"6_11_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(6,13,0)+"6_13_0", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(8,11,0)+"8_11_0", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(8,13,0)+"8_13_0", "southwest", 0, 1);
    add_row_exit(SECTOR_PATH(7,11,0)+"7_11_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(7,13,0)+"7_13_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(6,12,0)+"6_12_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(8,12,0)+"8_12_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(6,11,0)+"6_11_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(6,13,0)+"6_13_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(8,11,0)+"8_11_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(8,13,0)+"8_13_0", "southwest", 0, 1);
}
