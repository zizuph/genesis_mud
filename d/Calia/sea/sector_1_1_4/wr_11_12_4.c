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

    make_the_room("You notice that the water seems somewhat brighter to " +
        "the southwest, indicating that you are within the southwest " +
        "part of the seaweed forest.\n\n",
        11, 12, 4);

    add_swim_exit(SECTOR_PATH(11,11,4)+"wr_11_11_4", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(11,13,4)+"wr_11_13_4", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(10,12,4)+"wr_10_12_4", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(12,12,4)+"wr_12_12_4", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(10,11,4)+"wr_10_11_4", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(10,13,4)+"wr_10_13_4", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(12,11,4)+"wr_12_11_4", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(12,13,4)+"wr_12_13_4", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(11,12,3)+"wr_11_12_3", "up", 0, 0);
}
