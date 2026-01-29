/*
 * /d/Rhovanion/common/rhun/camp/camp24.c
 *
 * A path in the barbarian camp.
 */

inherit "/d/Rhovanion/common/rhun/camp/room";

#include "/d/Rhovanion/defs.h"

create_room()
{
  set_long("You are walking along a path in the west part of " +
           "the barbarian camp. To the east is a huge tent made " +
           "of gray canvas, while to the west, a palisade blocks" +
           "all movement. The path continues north and " +
           "southeast.\n");
  set_short("On a path in the barbarian camp");

  add_exit(CAMP_DIR + "camp15", "north", "@@trygo");
  add_exit(CAMP_DIR + "camp27", "southeast", 0);

  add_item("tent", "This tent is really big. Maybe it's for storing " +
           "supplies. You can't really be sure, but maybe if you " +
           "could find the entrance...\n");

  /* There are 0-1 barbarians in this room after reset */
  MaxBar=1;
}

 
