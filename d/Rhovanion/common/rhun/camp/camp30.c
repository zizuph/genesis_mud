/*
 * /d/Rhovanion/common/rhun/camp/camp30.c
 *
 * A path in the barbarian camp.
 */

inherit "/d/Rhovanion/common/rhun/camp/room";

#include "/d/Rhovanion/defs.h"

create_room()
{
  set_long("You are walking along a path in the south part of " +
           "the barbarian camp. To the north is a huge tent made " +
           "of gray canvas, while to the south and west, a palisade " +
           "blocks all movement. The path continues east and " +
           "northwest.\n");
  set_short("On a path in the barbarian camp");

  add_exit(CAMP_DIR + "camp27", "northwest", "@@trygo");
  add_exit(CAMP_DIR + "camp31", "east", 0);

  add_item("tent", "This tent is really big. Maybe it's for storing " +
           "supplies. You can't really be sure, but maybe if you " +
           "could find the entrance...\n");
}

