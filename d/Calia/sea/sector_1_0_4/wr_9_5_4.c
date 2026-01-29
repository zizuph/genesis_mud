/*
  This room should contain the entrance to the shipwreck.

  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

  Hole block added 17/5/98 by Maniac
*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_1_0_4_room";

#define SHIPWRECK_ENTRANCE   "/d/Calia/sea/shipwreck/lower/lower1"

void
create_water_room()
{
    make_the_room("\n", 9, 5, 4);

    add_swim_exit(SECTOR_PATH(9,4,4)+"wr_9_4_4", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(9,6,4)+"wr_9_6_4", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(8,5,4)+"wr_8_5_4", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(10,5,4)+"wr_10_5_4", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(8,4,4)+"wr_8_4_4", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(8,6,4)+"wr_8_6_4", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(10,4,4)+"wr_10_4_4", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(10,6,4)+"wr_10_6_4", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(9,5,3)+"wr_9_5_3", "up", 0, 0);
}


int
swim_hole(string str)
{
    notify_fail(capitalize(query_verb()) + " where?\n");

    if (!stringp(str) || !strlen(str))
        return 0;

    if (str == "through hole" || str == "into ship" ||
        str == "into hole" || str == "ship" || str == "hole" ||
        str == "wreck" || str == "shipwreck" ||
        str == "into wreck" || str == "into shipwreck") {
        write("You swim through the hole and into the shipwreck beyond.\n");
        tell_room(environment(TP),QCTNAME(TP)+" leaves swimming into the "+
           "hole in the hull.\n",TP);
        TP->move_living("M",SHIPWRECK_ENTRANCE);
        tell_room(environment(TP),QCTNAME(TP)+" arrives through the hole "+
            "in the wall.\n",TP);
        return 1;
    }

    return 0;
}

void
init()
{
    ::init();
    add_action(swim_hole, "enter"); 
    add_action(swim_hole, "swim"); 
}
