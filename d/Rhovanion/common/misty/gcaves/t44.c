/* goblin caves */
inherit "/d/Rhovanion/common/misty/gcaves/room_g";
#include "/d/Rhovanion/defs.h"

#define CAVE_DIR MISTY_DIR + "gcaves/"

void create_cave()
{
  add_exit(CAVE_DIR + "t45", "southwest");
  add_exit(CAVE_DIR + "t47", "northwest");
  add_exit(CAVE_DIR + "t43", "east");
  set_guards(5);
}