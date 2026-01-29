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

    make_the_room("Every direction looks the same here, you must be deep " +
        "within the heart of the seaweed forest. You look upwards, " +
        "hoping for a glimpse of brighter waters, but the massive stalks " +
        "of seaweed are tightly intertwining high above you, giving you " +
        "a strange sense of vertigo, only backwards.\n\n",
        10, 11, 4);

    add_swim_exit(SECTOR_PATH(10,10,4)+"wr_10_10_4", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(10,12,4)+"wr_10_12_4", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(9,11,4)+"wr_9_11_4", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(11,11,4)+"wr_11_11_4", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(9,10,4)+"wr_9_10_4", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(9,12,4)+"wr_9_12_4", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(11,10,4)+"wr_11_10_4", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(11,12,4)+"wr_11_12_4", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(10,11,3)+"wr_10_11_3", "up", 0, 0);
}
