/* goblin caves */
inherit "/d/Rhovanion/common/misty/gcaves/room";
#include "/d/Rhovanion/defs.h"

#define CAVE_DIR MISTY_DIR + "gcaves/"

void create_cave()
{
  add_exit(CAVE_DIR + "t33", "southwest");
  add_exit(CAVE_DIR + "t31", "northeast");
  set_pull(CAVE_DIR+"t04", "southeast");
}