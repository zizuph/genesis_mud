/* goblin caves */
#include "../local.h"

inherit CAVE_BASE;

void create_cave()
{
    add_exit(CAVE_DIR + "t34", "northwest");
    add_exit(CAVE_DIR + "t32", "northeast");

    set_pull(CAVE_DIR+"t02", "south");
}
