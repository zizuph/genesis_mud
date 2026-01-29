/* goblin caves */
inherit "/d/Rhovanion/common/misty/gcaves/room";
#include "/d/Rhovanion/defs.h"

#define CAVE_DIR MISTY_DIR + "gcaves/"

void create_cave()
{
  add_exit(CAVE_DIR + "t46", "southwest");
  add_exit(CAVE_DIR + "t44", "southeast");
  add_exit(CAVE_DIR + "t48", "north");
}