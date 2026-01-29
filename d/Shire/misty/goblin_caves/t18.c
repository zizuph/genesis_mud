/* goblin caves */
#include "../local.h"

inherit CAVE_BASE;

void create_cave()
{
    add_exit(CAVE_DIR + "t15", "north");
    add_exit(CAVE_DIR + "t19", "west");
    add_exit(CAVE_DIR + "t17", "east");
}
