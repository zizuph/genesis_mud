/* goblin caves */
inherit "/d/Rhovanion/common/misty/gcaves/room";
#include "/d/Rhovanion/defs.h"

#define CAVE_DIR MISTY_DIR + "gcaves/"

void create_cave()
{
  add_exit(CAVE_DIR + "t05", "northeast");
  add_exit(CAVE_DIR + "t03", "southwest");

  set_pull(CAVE_DIR+"t28", "southeast");
  set_push(CAVE_DIR+"t32", "northwest");
}