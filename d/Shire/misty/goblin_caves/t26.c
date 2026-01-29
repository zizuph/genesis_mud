/* goblin caves */
#include "../local.h"

inherit CAVE_BASE;

void create_cave()
{
    add_exit(CAVE_DIR + "t29", "north");
    add_exit(CAVE_DIR + "t27", "west");
    add_exit(CAVE_DIR + "t25", "east");
}
