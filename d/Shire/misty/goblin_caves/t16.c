/* goblin caves */
#include "../local.h"

inherit CAVE_BASE;

void create_cave()
{
    add_exit(CAVE_DIR + "t17", "south");
    add_exit(CAVE_DIR + "t15", "west");
}
