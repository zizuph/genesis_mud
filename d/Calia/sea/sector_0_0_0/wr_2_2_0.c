/*
  A room in the sea area off the west coast of Calia.
  Contains a rock that you can climb to reach the mermaid,  
  part of the mermaid quest. 

  Coded by Maniac, Jan 96, modified 6/9/96. 

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

#define ROCK (SECTOR_PATH(2,2,0)+"rock") 

inherit "/d/Calia/sea/std/sector_0_0_0_room";

void
create_water_room()
{
    make_the_room(" A particularly large granite rock juts out of the " +
                  "water here.\n", 2, 2, 0);

    add_item((({"rock", "granite rock", "large rock",
      "boulders", "line of boulders"})),
      "A particularly large granite rock, with a flat rounded top " +
      "is in front of you. It looks like you might be able to climb it.\n");

    add_swim_exit(SECTOR_PATH(2,1,0)+"wr_2_1_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(2,3,0)+"wr_2_3_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(3,2,0)+"wr_3_2_0", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(3,1,0)+"wr_3_1_0", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(3,3,0)+"wr_3_3_0", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(2,2,1)+"wr_2_2_1", "down", 0, 2);
    add_row_exit(SECTOR_PATH(2,1,0)+"wr_2_1_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(2,3,0)+"wr_2_3_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(3,2,0)+"wr_3_2_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(3,1,0)+"wr_3_1_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(3,3,0)+"wr_3_3_0", "southwest", 0, 1);
}


int
climb_rock(string str)
{
    notify_fail("Climb what?\n");
    if (str== "rock" || str == "granite rock" ||
        str == "rock" || str == "boulder" || str == "the rock") {
            this_player()->move_living("climbing the rock", ROCK, 1);
            return 1;
    }
    return 0;
}

void
init()
{
    ::init();
    add_action(climb_rock, "climb");
}

