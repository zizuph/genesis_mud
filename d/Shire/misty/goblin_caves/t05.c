/* goblin caves */
#include "../local.h"

inherit CAVE_BASE;

void create_cave()
{
    add_exit(CAVE_DIR + "t06", "north");
    add_exit(CAVE_DIR + "t04", "southwest");
}
