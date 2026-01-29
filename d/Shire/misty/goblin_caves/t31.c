/* goblin caves */
#include "../local.h"

inherit CAVE_BASE;

void create_cave()
{
  add_exit(CAVE_DIR + "t32", "southwest");
  add_exit(CAVE_DIR + "t35", "west");
  add_exit(CAVE_DIR + "t30", "northeast");
}
