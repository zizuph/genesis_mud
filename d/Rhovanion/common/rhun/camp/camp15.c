/*
 * /d/Rhovanion/common/rhun/camp/camp15.c
 *
 * A crossing of paths in the barbarian camp.
 */

inherit "/d/Rhovanion/common/rhun/camp/room";

#include "/d/Rhovanion/defs.h"

create_room()
{
  set_long("You are in the east part of the barbarian camp. There " +
           "are several paths going away from here. To the west is a " +
           "small tent. To the east is a wide path going past the " +
           "huge tent southeast of here. To the south, the path " +
           "follows the palisade which is built around the camp, and " +
           "to the north it passes more tents.\n");
  set_short("A crossing of paths in the barbarian camp");

  add_exit(CAMP_DIR + "camp24", "south", 0);
  add_exit(CAMP_DIR + "camp12", "north", "@@trygo");
  add_exit(CAMP_DIR + "tcamp10", "west", "@@trygo");
  add_exit(CAMP_DIR + "camp16", "east", "@@trygo");

  MaxBar=5;
}

 
