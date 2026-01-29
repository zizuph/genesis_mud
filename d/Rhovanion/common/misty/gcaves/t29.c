/* goblin caves */
inherit "/d/Rhovanion/common/misty/gcaves/room";
#include "/d/Rhovanion/defs.h"

#define CAVE_DIR MISTY_DIR + "gcaves/"

void create_cave()
{
  add_exit(CAVE_DIR+"t26", "south");
  add_exit(CAVE_DIR+"rat_farm", "west");

  set_push(CAVE_DIR+"hotel", "west");
}