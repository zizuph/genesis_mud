/* goblin caves */
#include "../local.h"

inherit CAVE_BASE;

void create_cave()
{
    add_exit(CAVE_DIR + "t12", "northeast");
    add_exit(CAVE_DIR + "t14", "east");
}
