/* goblin caves */
#include "../local.h"

inherit CAVE_BASE;

void create_cave()
{
    add_exit(CAVE_DIR + "t18", "south");
    add_exit(CAVE_DIR + "t14", "west");
    add_exit(CAVE_DIR + "t16", "east");
    add_exit(CAVE_DIR + "t11", "north");
    add_exit(CAVE_DIR + "t19", "southwest");
}
