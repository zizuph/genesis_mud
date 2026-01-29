/* goblin caves */
#include "../local.h"

inherit CAVE_BASE;

void create_cave()
{
    add_exit(CAVE_DIR + "shop", "west");
    add_exit(CAVE_DIR + "bank", "northwest");
    set_pull(CAVE_DIR+"t34", "north");
}
