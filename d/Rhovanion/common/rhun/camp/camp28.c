/*
 * /d/Rhovanion/common/rhun/camp/camp28.c
 *
 * A path in the barbarian camp.
 */

inherit "/d/Rhovanion/common/rhun/camp/room";

#include "/d/Rhovanion/defs.h"

create_room()
{
  set_long("You are walking along a path in the south part of " +
           "the barbarian camp. To the west is a huge tent made " +
           "of gray canvas. North, the path continues toward the " +
           "center of the camp, and to the south is a crossing of " +
           "paths.\n");
  set_short("On a path in the barbarian camp");

  add_exit(CAMP_DIR + "camp25", "north", "@@trygo");
  add_exit(CAMP_DIR + "camp1", "south", 0);

  add_item("tent", "This tent is really big. Maybe it's for storing " +
           "supplies. You can't really be sure, but maybe if you " +
           "could find the entrance...\n");
}

