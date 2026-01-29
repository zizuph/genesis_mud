/* goblin caves */
#include "../local.h"

inherit CAVE_BASE;

void create_cave()
{
    add_exit(CAVE_DIR + "t37", "south");
    add_exit(CAVE_DIR + "t38", "west");
    add_exit(CAVE_DIR + "t35", "east");
    set_push(CAVE_DIR+"t45", "north");
}
