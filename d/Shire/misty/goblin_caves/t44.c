/* goblin caves */
#include "../local.h"

inherit CAVE_GUARD_ROOM;

void create_cave()
{
    add_exit(CAVE_DIR + "t45", "southwest");
    add_exit(CAVE_DIR + "t47", "northwest");
    add_exit(CAVE_DIR + "t43", "east");
    set_guards(5);
}
