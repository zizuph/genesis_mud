/* goblin caves */
#include "../local.h"

inherit CAVE_BASE;

void create_cave()
{
    add_exit(CAVE_DIR + "t23", "south");
    add_exit(CAVE_DIR + "t21", "west");
}
