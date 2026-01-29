/* goblin caves */
#include "../local.h"

inherit CAVE_BASE;

void create_cave()
{
    add_exit(CAVE_DIR + "t15", "northeast");
    add_exit(CAVE_DIR + "t18", "east");
}
