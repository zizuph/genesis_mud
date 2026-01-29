/* goblin caves */
inherit "/d/Rhovanion/common/misty/gcaves/room";
#include "/d/Rhovanion/defs.h"

#define CAVE_DIR MISTY_DIR + "gcaves/"

void create_cave()
{
  add_exit(CAVE_DIR + "t29", "north");
  add_exit(CAVE_DIR + "t27", "west");
  add_exit(CAVE_DIR + "t25", "east");
}