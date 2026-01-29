/* goblin caves */
#include "../local.h"

inherit CAVE_BASE;

void create_cave()
{
    add_exit(CAVE_DIR + "t39", "west");
    add_exit(CAVE_DIR + "t36", "east");
}
