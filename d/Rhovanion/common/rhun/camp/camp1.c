/*
 * /d/Rhovanion/common/rhun/camp/camp1.c
 *
 * A crossing of paths in the barbarian camp.
 */

inherit "/d/Rhovanion/common/rhun/camp/room";

#include "/d/Rhovanion/defs.h"

create_room()
{
  set_long("You are in the south part of the barbarian camp. There " +
           "are several paths going away from here. To the south is " +
           "the guard post you passed entering the camp. To the north " +
           "is a wide path going past the huge tent northwest of here. " +
           "East and west, paths follow the palisade which is built " +
           "around the camp.\n");
  set_short("A crossing of paths in the barbarian camp");

  add_exit(CAMP_DIR + "guardpost", "south", 0);
  add_exit(CAMP_DIR + "camp28", "north", "@@trygo");
  add_exit(CAMP_DIR + "camp31", "west", "@@trygo");
  add_exit(CAMP_DIR + "camp32", "east", "@@trygo");

  /* There are 1-3 barbarians in this room after reset */
  MaxBar = 3;
}

