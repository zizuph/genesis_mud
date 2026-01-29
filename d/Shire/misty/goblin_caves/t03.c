/* goblin caves */
#include "../local.h"

inherit CAVE_GUARD_ROOM;

void create_cave()
{
    add_exit(CAVE_DIR + "t10", "south");
    add_exit(CAVE_DIR + "t02", "west");
    add_exit(CAVE_DIR + "t04", "northeast");
    set_guards(3);
}
