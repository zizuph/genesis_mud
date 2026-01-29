/* goblin caves */
#include "../local.h"

inherit CAVE_BASE;


void create_cave()
{
    add_exit(CAVE_DIR + "t15", "south");
    add_exit(CAVE_DIR + "t12", "west");
    add_exit(CAVE_DIR + "t10", "east");

    set_push(CAVE_DIR+"t02", "north");
}
