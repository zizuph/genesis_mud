/* goblin caves */
#include "../local.h"

inherit CAVE_BASE;

void create_cave()
{
    add_exit(CAVE_DIR + "t46", "southwest");
    add_exit(CAVE_DIR + "t44", "southeast");
    add_exit(CAVE_DIR + "t48", "north");
}
