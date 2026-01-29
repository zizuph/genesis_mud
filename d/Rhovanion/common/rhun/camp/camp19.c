/*
 * /d/Rhovanion/common/rhun/camp/camp19.c
 *
 * The middle of the barbarian camp.
 */

inherit "/d/Rhovanion/common/rhun/camp/room";

#include "/d/Rhovanion/defs.h"

create_room()
{
  set_long("You are standing at a crossing of paths in the middle " +
           "part of the camp." +
           "\n");
  set_short("A crossing of paths in the barbarian camp");

  add_exit(CAMP_DIR + "camp25", "south", 0);
  add_exit(CAMP_DIR + "camp13", "north", "@@trygo");
  add_exit(CAMP_DIR + "camp18", "west", "@@trygo");
  add_exit(CAMP_DIR + "camp20", "east", "@@trygo");
  add_exit(CAMP_DIR + "wcamp2", "southwest", "@@trygo");
  add_exit(CAMP_DIR + "gcamp1", "northeast", "@@trygo");

  /* There are 2-5 barbarians in this room after reset */
  MaxBar = 5;
}

