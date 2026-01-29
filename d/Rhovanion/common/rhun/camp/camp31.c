/*
 * /d/Rhovanion/common/rhun/camp/camp31.c
 *
 * A path in the barbarian camp.
 */

inherit "/d/Rhovanion/common/rhun/camp/room";

#include "/d/Rhovanion/defs.h"

create_room()
{
  set_long("You are walking along a path in the south part of " +
           "the barbarian camp. To the north is a huge tent made " +
           "of gray canvas, while to the south, a palisade blocks " +
           "all movement. To the east is a crossing of paths, and " +
           "to the west, the path continues along the palisade.\n");
  set_short("On a path in the barbarian camp");

  add_exit(CAMP_DIR + "camp30", "west", "@@trygo");
  add_exit(CAMP_DIR + "camp1", "east", 0);

  add_item("tent", "This tent is really big. Maybe it's for storing " +
           "supplies. You can't really be sure, but maybe if you " +
           "could find the entrance...\n");

  /* There are 0-1 barbarians in this room after reset */
  MaxBar = 1;
}

