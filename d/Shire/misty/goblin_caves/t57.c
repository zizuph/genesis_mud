/* goblin caves */
#include "../local.h"

inherit CAVE_BASE;

void create_cave()
{
    add_exit(CAVE_DIR + "t58", "southeast");
    add_exit(CAVE_DIR + "t56", "west");
}
