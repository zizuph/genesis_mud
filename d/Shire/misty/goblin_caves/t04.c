/* goblin caves */
#include "../local.h"

inherit CAVE_BASE;

void create_cave()
{
    add_exit(CAVE_DIR + "t05", "northeast");
    add_exit(CAVE_DIR + "t03", "southwest");

    set_pull(CAVE_DIR+"t28", "southeast");
    set_push(CAVE_DIR+"t32", "northwest");
}
