/* goblin caves */
#include "../local.h"

inherit CAVE_BASE;

void create_cave()
{
  add_exit(CAVE_DIR + "t24", "south");
  add_exit(CAVE_DIR + "t22", "north");
}
