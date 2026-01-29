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
    make_the_room("\n", 12, 12, 0);

    add_swim_exit(SECTOR_PATH(12,11,0)+"12_11_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(12,13,0)+"12_13_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(11,12,0)+"11_12_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(13,12,0)+"13_12_0", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(11,11,0)+"11_11_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(11,13,0)+"11_13_0", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(13,11,0)+"13_11_0", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(13,13,0)+"13_13_0", "southwest", 0, 1);
    add_row_exit(SECTOR_PATH(12,11,0)+"12_11_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(12,13,0)+"12_13_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(11,12,0)+"11_12_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(13,12,0)+"13_12_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(11,11,0)+"11_11_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(11,13,0)+"11_13_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(13,11,0)+"13_11_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(13,13,0)+"13_13_0", "southwest", 0, 1);
}
