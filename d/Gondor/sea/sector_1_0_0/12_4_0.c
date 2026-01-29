/*
  A room in the Bay of Belfalas near Tolfalas island.

  Palmer - Aug 24, 2006

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Gondor/sea/sector_1_0_0/sector_room";

#include "gull.h"

void
create_water_room()
{
    make_the_room("\n", 12, 4, 0);

    add_swim_exit(SECTOR_PATH(12,3,0)+"12_3_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(12,5,0)+"12_5_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(11,4,0)+"11_4_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(13,4,0)+"13_4_0", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(11,3,0)+"11_3_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(11,5,0)+"11_5_0", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(13,3,0)+"13_3_0", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(13,5,0)+"13_5_0", "southwest", 0, 1);
    add_row_exit(SECTOR_PATH(12,3,0)+"12_3_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(12,5,0)+"12_5_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(11,4,0)+"11_4_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(13,4,0)+"13_4_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(11,3,0)+"11_3_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(11,5,0)+"11_5_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(13,3,0)+"13_3_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(13,5,0)+"13_5_0", "southwest", 0, 1);
    reset_room();
}
