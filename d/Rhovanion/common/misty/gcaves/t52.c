/* goblin caves */
inherit "/d/Rhovanion/common/misty/gcaves/room";
#include "/d/Rhovanion/defs.h"

#define CAVE_DIR MISTY_DIR + "gcaves/"

void create_cave()
{
  add_exit(CAVE_DIR + "t53", "north");
  add_exit(CAVE_DIR + "t51", "southwest");
}

void reset_room(){}
