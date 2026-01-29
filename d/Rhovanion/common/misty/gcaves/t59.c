/* goblin caves */
inherit "/d/Rhovanion/common/misty/gcaves/room_g";
#include "/d/Rhovanion/defs.h"

#define CAVE_DIR MISTY_DIR + "gcaves/"

void create_cave()
{
  add_exit(MISTY_DIR+"p20", "east");
  add_exit(CAVE_DIR+"t58", "west");
  set_guards(2);
}
