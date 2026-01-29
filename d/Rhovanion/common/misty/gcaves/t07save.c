/* goblin caves */
inherit "/d/Rhovanion/common/misty/gcaves/room_g";
#include "/d/Rhovanion/defs.h"

#define CAVE_DIR MISTY_DIR + "gcaves/"

void create_cave()
{
  add_exit(CAVE_DIR + "t20", "east");
  add_exit(CAVE_DIR + "t30", "west");
  add_exit(CAVE_DIR + "t40", "northeast");
  add_exit(CAVE_DIR + "t06", "southwest");
  add_exit(CAVE_DIR + "t08", "southeast");
  set_guards(7);
}