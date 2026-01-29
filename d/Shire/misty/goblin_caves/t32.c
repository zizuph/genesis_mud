/* goblin caves */
#include "../local.h"

inherit CAVE_BASE;

void create_cave()
{
    add_exit(CAVE_DIR + "t33", "southwest");
    add_exit(CAVE_DIR + "t31", "northeast");
    set_pull(CAVE_DIR+"t04", "southeast");
}
