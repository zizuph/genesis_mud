/*
 * /d/Rhovanion/common/rhun/camp/camp25.c
 *
 * A path in the barbarian camp.
 */

inherit "/d/Rhovanion/common/rhun/camp/room";

#include "/d/Rhovanion/defs.h"

create_room()
{
  set_long("You are walking along a path in the central part of " +
           "the barbarian camp. To the west is a huge tent made " +
           "of gray canvas. North of here is a crossing of paths, " +
           "where you can see a high pole with some sort of standard " +
           "on top of it. To the south the path continues toward " +
           "the entrance of the camp.\n");
  set_short("On a path in the barbarian camp");

  add_exit(CAMP_DIR + "camp19", "north", "@@trygo");
  add_exit(CAMP_DIR + "camp28", "south", 0);

  add_item("tent", "This tent is really big. Maybe it's for storing " +
           "supplies. You can't really be sure, but maybe if you " +
           "could find the entrance...\n");
}

