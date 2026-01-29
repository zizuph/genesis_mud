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

    make_the_room("To the northeast, the water appears marginally " +
        "brighter, indicating that you are in the northeast edge of " +
        "the seaweed forest.\n\n",
        9, 10, 4);

    add_swim_exit(SECTOR_PATH(9,9,4)+"wr_9_9_4", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(9,11,4)+"wr_9_11_4", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(8,10,4)+"wr_8_10_4", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(10,10,4)+"wr_10_10_4", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(8,9,4)+"wr_8_9_4", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(8,11,4)+"wr_8_11_4", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(10,9,4)+"wr_10_9_4", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(10,11,4)+"wr_10_11_4", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(9,10,3)+"wr_9_10_3", "up", 0, 0);
}
