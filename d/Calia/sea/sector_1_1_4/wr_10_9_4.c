/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_1_1_4_room";

void
create_water_room()
{
    add_prop(ROOM_I_SEAWEED_FOREST, 1);

    make_the_room("The water seems to be a bit brighter to the east, " +
        "north and west, which you guess to mean you are in the northern " +
        "reaches of the seaweed forest.\n\n", 
        10, 9, 4);

    add_swim_exit(SECTOR_PATH(10,8,4)+"wr_10_8_4", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(10,10,4)+"wr_10_10_4", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(9,9,4)+"wr_9_9_4", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(11,9,4)+"wr_11_9_4", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(9,8,4)+"wr_9_8_4", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(9,10,4)+"wr_9_10_4", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(11,8,4)+"wr_11_8_4", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(11,10,4)+"wr_11_10_4", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(10,9,3)+"wr_10_9_3", "up", 0, 0);
}
