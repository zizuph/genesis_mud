/* goblin caves */
#include "../local.h"

inherit CAVE_BASE;

void create_cave()
{
    add_exit(CAVE_DIR + "t47", "northeast");
    add_exit(CAVE_DIR + "t45", "southeast");
}
