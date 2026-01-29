/* goblin caves */
inherit "/d/Rhovanion/common/misty/gcaves/room";
#include "/d/Rhovanion/defs.h"

#define CAVE_DIR MISTY_DIR + "gcaves/"

void create_cave()
{
  add_exit(CAVE_DIR + "t37", "south");
  add_exit(CAVE_DIR + "t38", "west");
  add_exit(CAVE_DIR + "t35", "east");
  set_push(CAVE_DIR+"t45", "north");
}