/* goblin caves */
#include "../local.h"

inherit CAVE_BASE;

void create_cave()
{
    add_exit(CAVE_DIR + "t22", "east");
    add_exit(CAVE_DIR + "t20", "west");
}
