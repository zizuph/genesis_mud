/* goblin caves */
#include "../local.h"

inherit CAVE_BASE;

void create_cave()
{
    add_exit(CAVE_DIR + "t31", "southwest");
    add_exit(CAVE_DIR + "t07", "east");
}
