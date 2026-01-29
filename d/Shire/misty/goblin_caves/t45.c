/* goblin caves */
#include "../local.h"

inherit CAVE_BASE;

void create_cave()
{
    add_exit(CAVE_DIR + "t44", "northeast");
    add_exit(CAVE_DIR + "t46", "northwest");
    set_pull(CAVE_DIR+"t36", "south");
}
